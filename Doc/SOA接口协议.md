# SOA 接口协议

* 皮这一下很开心小组
* 2018.3.15

---

## 概要

根据本项目的实际需求（详见需求文档），开发小组选用了前后端分离的 SOA 架构。本文档为基于此架构制定的接口协议。  
在本文档中，我们实现了基于 JSON 的接口规范，并详细定义了每个字段的格式及含义。为前后端面向服务接口进行编程提供了便利。  

* 为何选用 JSON 格式作为接口规范？  
    JSON API设计用来最小化请求的数量，以及客户端与服务器间传输的数据量。在高效实现的同时，无需牺牲可读性、灵活性和可发现性。

---

## 内容约定

* 后端职责  
    后端被前端通过子程序调用的方式运行；通过运行参数 argv 传入要分析的项目路径、分析结果的保存路径。经过运行分析之后，将分析结果通过本文档规定的 JSON 字段格式以文件的形式保存在前端指定的位置。

* 前端职责  
    前端需要根据用户操作，对后端程序传入合适的参数使之运行；在等待后端程序运行产生分析文件之后，读入文件中的文本，根据本文档的格式获取分析结果，从而生成用户展示界面。

---

## 接口规范

> 通过遵循共同的约定，可以提高开发效率，利用更普遍的工具，可以使开发者更加专注于程序的重点。

* 后端调用接口  
    前端可以使用任何可行的方式调用后端程序，例如
    ```cpp
    system("backEnd.exe arg1 arg2");
    execvp("backEnd.exe arg1 arg2");
    execvl("backEnd.exe arg1 arg2")
    ```
    传入参数类型及含义如下：

    Name|   Type|   Meaning 
    :-| :-| :-
    arg1| string|   需要分析的项目根目录
    arg2| string|   结果保存的文件目录

* JSON 语法  

    JSON 数据的书写格式是：名称/值对。  
    名称/值对包括字段名称（在双引号中），后面写一个冒号，然后是值：  
    ```json
    { "firstName" : "John" }
    ```

    JSON 值可以是：
    * 数字（整数或浮点数）
    * 字符串（在双引号中）
    * 逻辑值（true 或 false）
    * 数组（在方括号中）
    * 对象（在花括号中）
    * null

    JSON 对象在花括号中书写：  
    对象可以包含多个名称/值对：  
    ```json
    { "firstName":"John" , "lastName":"Doe" }
    ```

    JSON 对象可以嵌套使用，数组可以包含多个对象
    ```json
    {
        "firstName":"John",
        "familyMember":
        [
            {"Name" : "A"},
            {"Name" : "B"}
        ]
    }
    ```

* JSON 字段规范

    变量被调用信息
    ```json
    useInfo{
        "funcName"  :   "funcName",     /*调用的函数名称*/
        "usePos"    :   123             /*被调用的行号*/  
    }
    ```
    
    单变量汇总信息
    ```json
    varData{
        "varName"   :   "varName",      /*变量名*/
        "type"      :   "typeName",     /*变量类型*/
        "declarePos":   123,            /*声明的位置*/
        "useTimes"  :   123,            /*该变量被使用的次数*/
        "useList"   :   []              /*数组，存放类型为useInfo*/
    }
    ```

    文件汇总信息
    ```json
    fileData{
        "filePath"  :   "/path",        /*文件的绝对路径*/
        "varNum" :   123,            /*该文件包含的变量个数*/
        "varList"   :   []              /*存放varData类型元素*/
    }
    ```

    项目汇总信息
    ```json
    project{
        "fileNum":   123,            /*包含的文件个数*/
        "fileList"  :   []              /*存放fileData类型元素*/
    }
    ```

    后端需要保证传送的文件中包含且仅包含一个project类元素

---

### 附录

项目中所使用的字段及含义，备查

Name|Type|Meaning|Belongs
:-|:-|:-|:-
funcName|string|调用的函数名称|useInfo
usePos|int|被调用的行号|useInfo
-|-|-|-
varName|string|变量名|varData
type|string|变量类型|varData
declarePos|int|声明的位置|varData
useTimes|int|该变量被使用的次数|varData
useList|list\<useInfo\>|数组，存放类型为useInfo|varData
-|-|-|-
filePath|string|文件的绝对路径|fileData
varNum|int|该文件包含的变量个数|fileData
varList|list\<varData\>|fileData
-|-|-|-
fileNum|int|包含的文件个数|project
fileList|list\<fileData\>|存放fileData类型元素|project