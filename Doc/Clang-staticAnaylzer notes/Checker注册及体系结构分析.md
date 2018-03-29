# Checker 注册及体系结构分析

Checker 是 Clang 静态分析中的一个组件；Clang 静态分析器可以被 Clang 前端通过以下命令调用

```sh
clang --analyze
```

由于 Clang 是基于库的结构，因此 ClangAnalyzeChecker 等与静态分析相关的几个组件都以静态链接库的形式作为独立模块存放在 Clang\lib 目录下。  
模块化的组件结构使得 Clang lib 项目集合中的代码能够相互独立的存在，在文件调用关系中相对平行。因此，当对文件中的某个文件进行修改时，仅需对该文件以及上游项目进行重新生成。能够大量节约编译时间。

Clang 的静态分析类均继承自 Checker 类（clangStaticAnalyzerCore\Checker.h），在 ClangAnalyzeChecker 项目中添加自己的 checker 文件后需要进行注册操作，以保证自己的 checker 组件能够被整个项目正确载入。

在继承 Checker 类之后，可以实现一或多个回调函数接口；接口文档保存在 clangStaticAnalyzerCore\CheckerDocumentation.cpp 中；根据文档中的说明，每个接口对应着被分析代码的某种现象，当该现象产生时，将会触发该回调函数，将相关信息及上下文通过参数传入用户继承的函数中，供 checker 进行分析。  

根据测试，checker 的处理函数中可以正常进行输入输出流以及文件操作。

---

## 基于Visual Studio的项目内注册

简单来说，Static Analyzer Checker 的注册有两种方式

* 修改源代码以及 Cmake 列表，并重新对项目进行生成
* 先通过 Cmake 生成 Visual Studio 可读的项目文件，然后直接在项目中对代码进行修改。

由于对 Cmake 工具接触较少，我们小组选择了后者。

首先在 Visual Studio 中的 "Clang libraries\clangStaticAnalyzerCheckers\Source Files" 中添加自己的 checker.cpp 文件，以课题举例，命名为 "globalVarChecker.cpp"

![img](https://github.com/Reskip/global-variable-analysis/blob/master/Doc/Clang-staticAnaylzer%20notes/img/0_0.png)

在 "libraries\clangStaticAnalyzerCheckers\TableGen descriptions\Checkers.td" 中添加自己 checker 的注册信息。根据协议，我们的 checker 应当分类在 alpha （即试验区）中;

![img](https://github.com/Reskip/global-variable-analysis/blob/master/Doc/Clang-staticAnaylzer%20notes/img/0_1.png)

红框区域即添加的注册信息，该注册信息将会被其余组件处理生成 .inc 文件，并通过 \#include 指令，在本模块编译前动态修改代码，从而动态生成本 checker 的注册函数。

红框中的信息分别表示

* 生成的 checker 注册接口名称
* 在 clang 中的 help 文本
* 该 checker 的源代码文件

在注册操作过后，就可以在自己的 checker 进行编辑等操作了。

---

## checker 类的回调函数接口

TODO
