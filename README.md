# 系统安装手册

## 完成Node.js安装

1. [HZxCzar/Czar-s-Bookstore: Creating your own bookstore. (github.com)](https://github.com/HZxCzar/Czar-s-Bookstore) 此处下载文件夹

2. 安装C++环境/使用vscode安装”C/C++“扩展 *建议Vscode并使用WTL环境*  **WTL安装[WSL安装和配置_配置wsl-CSDN博客](https://blog.csdn.net/qq_27096221/article/details/119685695)**

3. 安装Node.js，进入官网[Node.js](https://nodejs.org/en) 安装LTS款Node.js

4. 打开cmd（Windows+R打开运行并进入cmd)

5. 在cmd中输入以下指令`
   
   ```
   VERSION=v20.10.0
    DISTRO=linux-x64
    sudo mkdir -p /usr/local/lib/nodejs
    sudo tar -xJvf node-$VERSION-$DISTRO.tar.xz -C /usr/local/lib/nodejs
   ```
   
   ```
   sudo ln -s /usr/local/lib/nodejs/node-$VERSION-$DISTRO/bin/node /usr/bin/nodesudo ln -s /usr/local/lib/nodejs/node-$VERSION-$DISTRO/bin/npm /usr/bin/npm
   
   sudo ln -s /usr/local/lib/nodejs/node-$VERSION-$DISTRO/bin/npx /usr/bin/npx
   ```

*ps：此处使用虚拟机才需写入sudo，后续指令虚拟机中无法执行可以加上前缀sudo尝试*

## 配置插件

**你可以通过以下指令查看你的安装状态**

```
Node -v
npm -v
```

### 安装soket库

*文件夹中自带soket文件，无法使用才需进行此步*

` npm install soket.io`

## 启动程序

**打开命令行cmd输入**

`cd /Bookstore/Node`

**进入后执行**

`Node SocketServer.js`

**Ctrl点击提示网页即可进入Web**

#### TIPS：

**设计架构->开发文档**

**操作方法->用户手册**


