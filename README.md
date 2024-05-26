**Written on**

![Proteus](https://img.shields.io/badge/Proteus-black?style=for-the-badge&logo=Proteus&logoColor=000&labelColor=fff)
![Atmel](https://img.shields.io/badge/Atmel_-black?style=for-the-badge&logo=amazonec2&logoColor=000&labelColor=fff)
![c](https://img.shields.io/badge/c_-black?style=for-the-badge&logo=c&logoColor=000&labelColor=fff)

**Works  with**
*Atmega32 & Atmega16, and all subversions of them.*
***
**Hint**
- **ex**: exercises from AVR projects file.
- **clsex**: exercises given in the class.


**File tree example**
|Atmel projects |Proteus files |HEX files |
|----------------|-----------------|------------------|
|`./atmlcod-pro/`|`./proteus-pro/'`|`'./avrhexs-pro/'`|

**How to use**
```mermaid
graph LR
A[Clone Repo]  --> B((Edit code & Build))
A --> C(Run Proteus file)
B --> E((Run in Proteus))
E --> D{FINISH}
C --> D
```