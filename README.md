# 我的 dwm 配置
dwm 是 X 服务的一个非常轻量的、快速的动态窗口管理器。

## 安装前的准备
在安装 dwm 之前，你需要有 `Xlib` 头文件。

## 安装
首先，编辑 `config.mk` 这个文件来匹配你的本地设置（dwm 默认安装到 `/usr/local` 命名空间下）。  
然后，运行以下命令来编译和安装 dwm（可能需要作为 root 用户来执行命令）。  

```
make clean install
```

## 运行
#### 使用 startx 启动 dwm
把下面这一行添加到你的 `.xinitrc` 中，以使用 startx 来启动 dwm。  

```
exec dwm
```

为了将 dwm 连接到一个特定的显示器，请确保 DISPLAY 环境变量设置正确，例如：  

```
DISPLAY=foo.bar:1 exec dwm
```

（这将在主机 foo.bar 的显示器 :1 上启动 dwm。）

为了在状态栏中显示信息，你可以在 `.xinitrc` 中这样启动 dwm（不过我的 dwm 会自动启动一个控制状态栏的脚本，所以不需要这样启动）：

```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
	sleep 1
done &
exec dwm
```

#### 使用登录管理器启动 dwm
把 `others` 文件夹里的 `dwm.desktop` 复制到 `/usr/share/xsessions` 这个文件夹下，之后在登录管理器选择启动 dwm 即可。

## 配置
Dwm 的配置是通过自定义 `config.h` 和重新编译安装来实现的。

## 补丁
- [alphasystray.diff](https://github.com/theniceboy/dwm/blob/master/patches/alphasystray.diff) （[alpha](https://dwm.suckless.org/patches/alpha/) 和 [systray](https://dwm.suckless.org/patches/systray/) 补丁的集合，让状态栏能够半透明并且增加了系统托盘）
- [dwm-autostart-20161205-bb3bd6f.diff](https://dwm.suckless.org/patches/autostart/) （让 dwm 能在启动时顺便运行一个脚本）
- [dwm-awesomebar-20191003-80e2a76.diff](https://dwm.suckless.org/patches/awesomebar/) （让状态栏显示当前桌面的所有窗口的名称）
- [dwm-fullscreen-6.2.diff](https://dwm.suckless.org/patches/fullscreen/) （让窗口可以全屏）
- [dwm-hide_vacant_tags-6.2.diff](https://dwm.suckless.org/patches/hide_vacant_tags/) （让状态栏只显示有窗口的桌面的标签）
- [dwm-noborder-6.2.diff](https://dwm.suckless.org/patches/noborder/) （当只有一个窗口时，去除窗口的边框）
- [dwm-pertag-20170513-ceac8c9.diff](https://dwm.suckless.org/patches/pertag/) （不同的桌面保持不同的窗口管理方式）
- [dwm-rotatestack-20161021-ab9571b.diff](https://dwm.suckless.org/patches/rotatestack/) （能调整窗口摆放顺序）
- [dwm-scratchpad-6.2.diff](https://dwm.suckless.org/patches/scratchpad/) （能临时打开一个小窗口并在任意桌面都能显示）
- [dwm-vanitygaps-20190508-6.2.diff](https://dwm.suckless.org/patches/vanitygaps/) （在窗口之间增加一个小的空隙）

## 使用方法

**一些键位：**  
`Mod` 键为 `Windows` 键  
`Space` 键为空格键  
`<number>` 键为数字键  

---

**注意：**  
`dwm` 下的桌面其实并**不是**真正的桌面，而是显示打了某一个**标签**的某些窗口。  

**e.g.**  
假设我的电脑上有五个窗口，分别为 `google-chrome`，`st`，`NeoVim`，`Ranger`，`htop`。  
其中，每个窗口都打上了标签：

| 窗口                    | 标签 |
|-------------------------|------|
| `google-chrome` 和 `st` | `1`  |
| `NeoVim`                | `3`  |
| `Ranger` 和 `htop`      | `6`  |

那么，如果我切换到 `1` 号桌面，那么实际上就是显示打了 `1` 这个标签的窗口，即为显示 `google-chrome` 和 `st` 这两个窗口。  
接下来，我又给某些窗口增加了一些标签：

| 窗口                    | 标签       |
|-------------------------|------------|
| `google-chrome` 和 `st` | `1`        |
| `NeoVim`                | `3` 和 `5` |
| `Ranger` 和 `htop`      | `6` 和 `5` |

那么在现在，如果我切换到 `5` 号桌面，实际上就是显示打了 `5` 这个标签的窗口，即为显示 `NeoVim`、`Ranger`和`htop`。  
但需要注意的是，由于这三个窗口都各打了两个标签，所以在别的相应的桌面也能看到这些窗口，如切换到 `3` 号桌面也会显示 `NeoVim` 这个窗口。  

---
### 1 键盘快捷键
#### 1.1 移动焦点
| 快捷键  | 作用               |
|---------|--------------------|
| `Mod+i` | 往上（左）移动焦点 |
| `Mod+k` | 往下（右）移动焦点 |

#### 1.2 关于桌面和标签
| 快捷键                    | 作用                                                 |
|---------------------------|------------------------------------------------------|
| `Mod+Tab`                 | 切换到上一次浏览的桌面                               |
| `Mod+<number>`            | 切换到某一个桌面                                     |
| `Mod+Ctrl+<number>`       | 将某一个桌面的窗口和当前桌面的窗口一起浏览           |
| `Mod+0`                   | 将全部桌面的窗口一起浏览                             |
| `Mod+Shift+<number>`      | 用某个标签替换该窗口原来的标签（将窗口移至某个桌面） |
| `Mod+Ctrl+Shift+<number>` | 给某个窗口增加某个标签                               |
| `Mod+Shift+0`             | 给某个窗口增加全部的标签                             |

#### 1.3 打开软件
| 快捷键       | 作用                 |
|--------------|----------------------|
| `Mod+Return` | 打开 `st`            |
| `Mod+d`      | 打开 `dmenu`         |
| `Mod+c`      | 打开 `Google-Chrome` |

#### 1.4 更改窗口布局
| 快捷键             | 作用                                       |
|--------------------|--------------------------------------------|
| `Mod+Shift+t`      | 切换到平铺模式（`Tile`）                   |
| `Mod+Shift+f`      | 切换到浮动模式（`Float`）                  |
| `Mod+Shift+m`      | 切换到单页模式（`Monocle`）                |
| `Mod+f`            | 进入进入全屏模式                           |
| `Mod+Space`        | 切换到上一种窗口摆放方式                   |
| `Mod+Shift+Space`  | 将当前窗口切换到浮动模式/平铺模式          |
| `Mod+Shift+i`      | 将窗口往上（左）移动                       |
| `Mod+Shift+k`      | 将窗口往下（右）移动                       |
| `Mod+h`            | 将窗口横向分割                             |
| `Mod+p`            | 将窗口纵向分割                             |
| `Mod+j`            | 将窗口的纵向分割线左移                     |
| `Mod+l`            | 将窗口的纵向分割线右移                     |
| `Mod+Shift+Return` | 将当前窗口变成主窗口，或者放到栈区域的顶部 |

#### 1.5 关于声音的控制
| 快捷键       | 作用          |
|--------------|---------------|
| `Mod+Ctrl+i` | 把声音升高 5% |
| `Mod+Ctrl+k` | 把声音降低 5% |
| `Mod+Ctrl+m` | 打开/关闭声音 |

#### 1.6 关于窗口之间的缝隙
**注：`1` 表示窗口与窗口之间，`2` 表示窗口与显示屏边缘之间**
| 快捷键            | 作用                                     |
|-------------------|------------------------------------------|
| `Mod+Alt+0`       | 打开/关闭 `1` 和 `2` 的缝隙              |
| `Mod+Alt+Shift+0` | 把 `1` 和 `2` 之间的缝隙切换到默认的大小 |
| `Mod+Alt+j`       | 放大 `1` 和 `2` 的缝隙                   |
| `Mod+Alt+l`       | 缩小 `1` 和 `2` 的缝隙                   |
| `Mod+Alt+Shift+j` | 放大 `2` 的缝隙                          |
| `Mod+Alt+Shift+l` | 缩小 `2` 的缝隙                          |
| `Mod+Alt+Ctrl+j`  | 放大 `1` 的缝隙                          |
| `Mod+Alt+Ctrl+l`  | 缩小 `1` 的缝隙                          |
| `Mod+u`           | 放大 `1` 的横向的窗口分割缝隙            |
| `Mod+o`           | 缩小 `1` 的横向的窗口分割缝隙            |
| `Mod+Ctrl+u`      | 放大 `1` 的纵向的窗口分割缝隙            |
| `Mod+Ctrl+o`      | 缩小 `1` 的纵向的窗口分割缝隙            |
| `Mod+Alt+u`       | 放大 `2` 的横向的缝隙                    |
| `Mod+Alt+o`       | 缩小 `2` 的横向的缝隙                    |
| `Mod+Shift+u`     | 放大 `2` 的纵向的缝隙                    |
| `Mod+Shift+o`     | 缩小 `2` 的纵向的缝隙                    |

#### 1.7 其他功能
| 快捷键             | 作用                              |
|--------------------|-----------------------------------|
| `Mod+'`            | 打开/关闭 `scratchpad`            |
| `Mod+b`            | 打开/关闭状态栏                   |
| `Mod+Ctrl+q`       | 关闭当前窗口                      |
| `Mod+Ctrl+Shift+c` | 关闭 `dwm`                        |
| `Mod+,`            | 暂不了解该快捷键的功能            |
| `Mod+.`            | 暂不了解该快捷键的功能            |
| `Mod+Shift+,`      | 暂不了解该快捷键的功能            |
| `Mod+Shift+.`      | 暂不了解该快捷键的功能            |

### 2 鼠标点击
#### 2.1 更改窗口布局
| 鼠标动作                     | 作用                                                 |
|------------------------------|------------------------------------------------------|
| `左键状态栏上的当前模式标志` | 切换到上一种窗口摆放方式                             |
| `右键状态栏上的当前模式标志` | 切换到浮动模式（`Float`）                            |
| `左键状态栏上的窗口名称`     | 将焦点移至该窗口，或隐藏/显示该窗口                  |
| `中键状态栏上的窗口名称`     | 将当前焦点所在的窗口变成主窗口，或者放到栈区域的顶部 |
| `Mod+左键窗口并移动光标`     | 将当前窗口变为浮动窗口，并随鼠标移动而移动           |
| `Mod+中键窗口`               | 将当前窗口变为浮动窗口或取消浮动                     |
| `Mod+右键窗口并移动光标`     | 将当前窗口变为浮动窗口，并随鼠标的移动而改变大小     |

#### 2.2 打开软件
| 鼠标动作             | 作用      |
|----------------------|-----------|
| `中键状态栏上的信息` | 打开 `st` |

#### 2.3 关于桌面和标签
| 鼠标动作                     | 作用                                                 |
|------------------------------|------------------------------------------------------|
| `左键状态栏上的桌面标签`     | 切换到某一个桌面                                     |
| `右键状态栏上的桌面标签`     | 将某一个窗口和当前窗口一起浏览                       |
| `Mod+左键状态栏上的桌面标签` | 用某个标签替换该窗口原来的标签（将窗口移至某个桌面） |
| `Mod+右键状态栏上的桌面标签` | 给某个窗口增加某个标签                               |

