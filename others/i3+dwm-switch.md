# 窗口管理器无缝切换

<!-- vim-markdown-toc GFM -->

* [一、工具](#一工具)
* [二、配置lightdm](#二配置lightdm)
	* [制作dwm session desktop文件](#制作dwm-session-desktop文件)
* [三、配置xinitrc](#三配置xinitrc)
* [四、配置开机启动项](#四配置开机启动项)
	* [如何解决不同session不同的开机启动项](#如何解决不同session不同的开机启动项)
* [五、配置快捷键](#五配置快捷键)
* [六、dwm使用i3lock锁屏](#六dwm使用i3lock锁屏)

<!-- vim-markdown-toc -->

---

前言  
我们需要知道我们的目的是什么 `What I want`  
我们需要思考我们如何去做 `How to do`  
我们需要去做 `To do`

`like it` 我的目的是 `WM` 的无缝切换  
思考怎么去做:
1. 先要实现 `WM` 的切换
2. 减少 `WM` 对其它内容的耦合(下文的 `开机启动项` `快捷键`)
3. 将减少的部分统一起来

最后就是 `To do`
> 声明:This Document is not for everyone!

---

## 一、工具

1. `lightdm`
2. `dwm`
3. `i3`
4. `xbindkeys`
5. `xorg-xinit` 
6. `xorg-xsetroot`
7. `xss-lock`

> 注：`lightdm`非必须

---

## 二、配置lightdm

> 首先：请详细查看阅读 `/etc/lightdm/Xsession` 或 `/usr/share/lightdm.d/*` 了解 `lightdm` 登录机制

### 制作dwm session desktop文件
> 文件目录 `/usr/share/xsessions/anyname.desktop`  
> $ sudo vim /usr/share/xsessions/dwm.desktop
```shell
[Desktop Entry]
Encoding=UTF-8
Name=dwm
Comment=Dynamic window manager
Exec=dwm
Icon=dwm
Type=XSession
```
> `lightdm` 根据 `xdg-session` 选择会话  
> 注：环境变量 `XDG_SESSION_DESKTOP` 记录您当前使用的 `xsession`
>
> 附：我的 `dwm` [Github](https://github.com/KerrLiu/dwm)  
> 注：该 `dwm` 补丁较多，使用 `Mod4` 作为 `Mod` 键,默认终端为 `st` ，安装默认会生成 `xsession.desktop`  不建议使用

---

## 三、配置xinitrc

> 首先：请详细查看阅读 `$HOME/.xinitrc` OR `/etc/X11/xinit/xinitrc`
```shell
session=${1:-i3}

case $session in
    i3|i3wm) exec i3;;
    dwm)exec dwm;;
    *) exec $1;;
esac
```
> 注：如果您使用其它 `wm` OR `DE` 请修改上文  
> 注：你可以在 `tty` 下使用 `xinit session` OR `startx ~/.xinitrc session` 进入
>
> [xinit wiki](https://wiki.archlinux.org/index.php/xinit)

---
## 四、配置开机启动项
> 仔细阅读过 `lightdm` `Xsession` 脚本文件可以知道进入图形界面后会加载 `$HOME/.profile` 文件，那么我们的开机启动项可以放在该文件当中  
> 类似的有：
>
> 1. `.xprofile`
> 2. `.zprofile`
> 3. 等
>
> 注意：开机启动项可以放在任意开机加载的文件当中不过需要注意以下几点  
> 1.使用用户的开机加载文件  
> 2.使用不重复加载的文件  
> 3.将开机启动项单独放置在一个脚本当中  
> 4.不将开机启动项放置在 `WM` OR `DE` 配置文件当中

> 使用 `XDG_Autostart` 配置开机启动项  
> 配置文件路径 `$HOME/.config/autostart`  
> [AutostartWiki](https://wiki.archlinux.org/index.php/XDG_Autostart)

### 如何解决不同session不同的开机启动项
> 在上面我们提到过 `XDG_SESSION_DESKTOP`  这个变量  
> 那么我们的开机启动项脚本就可以根据这个变量进行选择性启动
```shell
if [ $XDG_SESSION_DESKTOP == "i3" ]; then
         
else
               
fi
```

---


## 五、配置快捷键
> 说明：大多数 `WM` OR `DE` 可以配置快捷键，我们为什么不试试统一呢  
> `xbindkeys` 安装 `sudo pacman -S xbindkeys`  
>
> 说明：`xbindkeys` 默认配置文件 `$HOME/.xbindkeysrc`  
> 生成：`xbindkeys -d > $HOME/.xbindkeysrc` 这会生成一个默认的配置文件  
> 启动：`xbindkeys`  
> 注：那么我们将 `xbindkeys` 加入开机启动项当中吧

`xbindkeys` 语法(注:默认生成的配置文件中已有说明)

```shell
"google-chrome-stable"
  Mod4+b

"xbacklight -inc 5"
  XF86MonBrightnessUp
```
> 注:请仔细阅读配置文件的注释说明

---


## 六、dwm使用i3lock锁屏
> 首先查看 `i3config` 找到锁屏配置  
> exec --no-startup-id xss-lock --transfer-sleep-lock -- i3lock -i "imgpath"
>
> `xss-lock` 使用外部储物柜作为X屏幕保护程序 如无需安装  
> `i3lock` i3wm默认锁屏程序(非必须)  
> 注: 只使用 `dwm` 这一个WM 可单独安装 `i3lock` 或其它锁屏程序
>
> 在 `dwm` 开启启动项添加xss-lock --transfer-sleep-lock -- i3lock -i "imgpath"  
> 注: 请勿使 `i3` 重复加载 `xss-lock`

休眠时间设置:

```shell
xset dpms 600
```
> 注: 最大值600s 可放进开机启动脚本中

[Xss-lock详情介绍](https://www.mankier.com/1/xss-lock)

---
结语:

查询阅读 `文档` `Wiki` 是必要的  
当你花时间在阅读理解这些内容中到最后你会发现这些是如此通俗易懂且有用  
尽量查看阅读官方 `文档` 及 `Wiki` 其他个人 `博客` `文章` 是最后的选择  
我们不能将一切寄托于他人的理解,应更多的当作是一个方向  
最后推荐一个我一直看的 `Youtube` 频道 [Luke Smith](https://www.youtube.com/channel/UC2eYFnH61tmytImy1mTYvhA) 他的视频也许会让你难以理解但当你仔细理解并尝试你会发现非常有趣并且实用  
当然如果你看到一个戴着墨镜的秃头一个人坐在车里或者走在不知名的地方请及时退出因为你不会知道他要去哪,他要干啥,如果你愿意可以听听他说什么  

---

[^作者]: Kerr

