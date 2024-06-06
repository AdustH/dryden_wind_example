# Dryden Wind Turbulence Model

A c++ version of the Dryden Wind Turbulence Model in matlab.

因为项目要用到matlab中的紊流模型，但是主体程序又要用c++来写，所以用了一下matlab的代码生成 :blush:

代码所实现的功能如下图所示

![Image text](https://github.com/AdustH/img/blob/main/dryden_img01.png?raw=true)

 - dryden紊流强度修改在wenliu_data.cpp第57行，2U代表robability of exceedance of high-altitude intensity 是10e-2
 - 如果要调整时间步长，需要同步修改dryden中的时间步长，在wenliu.cpp第130行和841行
如果时间步长为0.0001，则第130行 >999；如果时间步长为0.001，则第130行>99
如果时间步长为0.0001，则第841行 =0.0001；如果时间步长为0.001，则第841行 =0.001

感谢b站大佬出的关于如何理解和使用matlab生成的c++代码的教程 :sob: 
