# 愉快的使用Dwm

<!-- vim-markdown-toc GFM -->

* [一、重新编译的情况](#一重新编译的情况)
* [二、依次分析这几种情况](#二依次分析这几种情况)
	* [1.更换字体配置](#1更换字体配置)
	* [2.打上新的补丁](#2打上新的补丁)
	* [3.修改dwm配色](#3修改dwm配色)
	* [4.修改热键绑定](#4修改热键绑定)
* [二、状态信息](#二状态信息)

<!-- vim-markdown-toc -->

---

`dwm` 一旦修改配置就需要重新编译安装  
这是作为 `dwm` 用户的常识

---

## 一、重新编译的情况

1. 更换字体配置
2. 打上新的补丁
3. 修改dwm配色
4. 修改热键绑定

> 注: 当然还有其它的调整选项

---

## 二、依次分析这几种情况

### 1.更换字体配置
```c
# config.h
static const char *fonts[] = { "monospace:size=10"};
```

> 从 `fonts[]` 我们知道这是一个数组我们可以在这个数组中存放多个字体名称
```c
# config.h
static const char *fonts[] = { "monospace:size=10", "monospace:size=10"};
```

> 更换字体配置的次数很少不在频繁编译范畴内

---

### 2.打上新的补丁

> 打补丁必然需要从新编译同时不在频繁编译的范畴内

---
### 3.修改dwm配色

```c
# config.h
static char normbgcolor[]     = "#222D31";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#dddddd";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#222D31";
static char selbgcolor[]      = "#222D31";
```

> 注: 以上为个人 `config` 配色变量请勿拷贝  
> 当然配色的改动情况很少但是配色的调整和统一是十分麻烦的  
> `xrdb` 补丁可以使用 `Xresources` 文件中定义的颜色值  
> 作为 `dwm` 的配色并且可以动态刷新配色  
> 注: 需先使用xrdb file 命令更新  
> [xrdb wiki](https://wiki.archlinux.org/index.php/X_resources) 

```c
# config.h

{ MODKEY, XK_F5, xrdb, {.v = NULL } },

# dwm.c

if (xrdb != NULL) {
  XRDB_LOAD_COLOR("dwm.color0", normbordercolor );
  XRDB_LOAD_COLOR("dwm.color8", selbordercolor  );
  XRDB_LOAD_COLOR("dwm.color0", normbgcolor     );
  XRDB_LOAD_COLOR("dwm.color4", normfgcolor     );
  XRDB_LOAD_COLOR("dwm.color6", selfgcolor      );
  XRDB_LOAD_COLOR("dwm.color0", selbgcolor      );
}
```

---

### 4.修改热键绑定

> 对于热键绑定的修改可能是最频繁的也是 `config.h` 中改动最多的地方  
> 对于程序的热键启动我们可以使用其他的热键绑定工具实现  
> 如 `sxhkd` `xbingkeys`  
> 但是对于 `dwm` 程序内置窗口调整布局更换功能也许只能在 `config` 中更改
```c
# config.h
{ MODKEY,           XK_0, view,       {.ui = ~0 } },
{ MODKEY|ShiftMask, XK_0, tag,        {.ui = ~0 } },
{ MODKEY,           XK_q, killclient, {0}         },
```
> 也许您会说这些内置功能的键绑定我也很少修改  
> 但是有没有存在这么一种情况:让某个程序在指定的 `tag` 打开  
> 很显然这在 `config.h` 中无法配置出来  
> 那么 `dwmc` 这个补丁可以解决这个问题  
> 以下为部分内容
```c
# config.h
static Signal signals[] = {
  /* signum           function */
  { "focusstack",     focusstack     },
  { "setmfact",       setmfact       },
  { "togglebar",      togglebar      },
  { "incnmaster",     incnmaster     },
  { "togglefloating", togglefloating },
  { "focusmon",       focusmon       },
  { "tagmon",         tagmon         },
  { "zoom",           zoom           },
  { "view",           view           },

```
```shell
# dwmc
#!/usr/bin/env sh

signal() {
  xsetroot -name "fsignal:$*"
}

case $# in
1)
  case $1 in
  setlayout | view | viewall | togglebar | togglefloating | zoom | killclient | quit)
    signal $1
    ;;
  *)
    echo "Unknown command or missing one argument."
    exit 1
    ;;
  esac
  ;;

```
> 我们通过使用 `dwmc` 脚本就可以向 `dwm` 发送信号  
> 例如实现在 `tag1` 中打开 `chrome` 浏览器  
> `google-chrome-stable & dwmc viewex 1` 可添加进热键绑定  
> 注: `tag` 从0计数

---

## 二、状态信息

> 我们在 `dwm` 的状态栏中显示系统状态信息通常是脚本+ `xsetroot -name "msg"`  
> 但是单纯的这样展示系统信息存在信息刷新时间间隔和资源频繁的使用问题  
> 当然我们可以设计一个很巧妙的脚本来科学的调度显示的信息  
> 例如不需要频繁刷新的信息给个较长的 `sleep` 时间需要刷新时通过 `kill` 掉这个 `sleep`  
> 这种脚本的编写是很繁琐并且不可靠的  
> `dwmblocks` 这个工具可以很好的解决这个问题  
> 它也依靠 `shell` 提供需要展示的信息同时它接受来自外部的 `signal`   
> 这样我们就可以根据定义的 `signal` 在外部控制 `dwmblocks`
```c
# blocks.h
static const Block blocks[] = {
  /*Icon*/   /*Command*/                              /*Update Interval*/  /*Update Signal*/
  {"🔊 ",    "amixer get Master | grep -o \"\\(\\[off\\]\\|[0-9]*%\\)\"",   0,   10},
  {"🔋 ",    "sed \"s/$/%/\" /sys/class/power_supply/BAT?/capacity",        5,   12},
  {"🕗 ",    "date '+%Y %b %d (%a) %I:%M%p'",                               60,   0},
};
```
> `pkill -RTMIN+Signal dwmblocks`  
> `pkill -RTMIN+12 dwmblocks` 就可以打断 `BAT` 信息的 `update interval` 从而刷新 `BAT`

---

[dwmblocks github](https://github.com/LukeSmithxyz/dwmblocks)

---
结语:  
祝各位 `dwm` 使用愉悦!

---

[^作者]: Kerr

