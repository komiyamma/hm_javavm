# hmJavaVM

![hmJavaVM v1.8.1](https://img.shields.io/badge/hmJavaVM-v1.8.1-6479ff.svg)
[![Apache 2.0](https://img.shields.io/badge/license-Apache_2.0-blue.svg?style=flat)](LICENSE)
![Hidemaru 8.73](https://img.shields.io/badge/Hidemaru-v8.73-6479ff.svg)
![Java 8.x](https://img.shields.io/badge/Java-v8.x-6479ff.svg?logo=java&logoColor=white)

秀丸マクロで「Javaと秀丸マクロをシームレスに近い形で利用する」ためのコンポーネントとなります。

[https://秀丸マクロ.net/?page=nobu_tool_hm_javavm](https://秀丸マクロ.net/?page=nobu_tool_hm_javavm)

## 概要

`hmJavaVM` は、高機能テキストエディタ「秀丸エディタ」のマクロ機能を、Java言語で記述できるようにするための連携コンポーネントです。
秀丸マクロからJavaのメソッドを呼び出したり、逆にJava側から秀丸エディタの機能（カーソル位置の取得、テキストの挿入、マクロ変数の操作など）を呼び出したりすることができ、Javaの持つ豊富なライブラリやエコシステムを秀丸マクロで活用することが可能になります。

### 主な機能

- **Java連携**: 秀丸マクロからJavaで記述されたクラスのstaticメソッドを呼び出すことができます。
- **秀丸API**: Javaコードから秀丸エディタの各種機能を呼び出すためのAPIを提供します。
- **シームレスな連携**: 秀丸マクロの変数とJavaの変数を相互にやり取りすることが可能です。

### 仕組み

このコンポーネントは、以下の主要なファイルで構成されています。

- `hmJavaVM.dll`: 秀丸エディタから直接呼び出されるC++製のネイティブライブラリです。このDLLがJava仮想マシン(JVM)の起動と管理を行います。
- `hmJavaVM.jar`: 秀丸エディタの機能を呼び出すためのJava APIや、ユーザーが作成したJavaクラスを格納するJARファイルです。
- `hmJavaVM.xml`: 使用するJava(JDK/JRE)に含まれる `jvm.dll` のパスを指定するための設定ファイルです。

### 動作環境

- **秀丸エディタ**: ver8.73 以上 (32bit版 / 64bit版)
- **Java**: Java 8系 (Oracle JDK, OpenJDKなど)
  - **注意**: Java 9以降のバージョンでは、クラスローダーの仕組みが変更されたため動作しません。

### **【重要】現在のステータス**

このコンポーネントは、Java 9以降の仕様変更への追随が困難であることや、Oracle社のライセンス体系の変遷などを理由に、開発者によって**非推奨 (deprecated)** とされています。