# OS-GCxGC
LMCS style open source GCxGC modulator

This is a guide on constructing the modulator used in my research papers. It is intended to be as thorough as possible to allow for those unfamiliar with coding or electronics to still be able to build this device.  
Hopefully it is all the info that you will need to build one. If you have any questions then feel free to reach out and ask (I have no permanent email address at present, but I will add this in when I can), I am always keen to help people access the power of GCxGC and MDGC!  
  
Construction folder will contain all the details for building the device including 3D models and step-by-step instructions (WIP, currently contains only the 3D files)  
Code folder contains the arduino code which should be well commented so people unfamiliar with C++ can make alterations to suit their modulating needs. There will be new versions with different functionality coming in future.

My goal is to eventually make this simple enough that it could be built as final year undergraduate research project so that GC×GC is easily accessible to anyone who wants to try it.  
Realistically this might only be feasible for undergraduates who already have some engineering/GC familiarity.  
  
  
  
Various free software exists for interpreting the results, I believe that openchrom can image 3D data, but I currently use propriatry software so cannot recommend any specific open source ones.
  
  
  
## Licensing

This project contains both hardware designs and software code, which are licensed separately:

- **Hardware designs** (in the `/Construction` directory and its subdirectories) are licensed under the [CERN Open Hardware License Version 2 - Weakly Reciprocal (CERN-OHL-W-2.0)](Construction/LICENSE). This license requires that any modifications to the hardware design be shared under the same license, but allows larger works that use the hardware via defined interfaces to be licensed differently.

- **Software code** (in the `/Code` directory and its subdirectories) is licensed under the [GNU General Public License Version 3 (GPL-3.0)](Code/LICENSE). This license ensures that software modifications remain free and open.

Please refer to the respective `LICENSE` files in each directory for the full license texts.

---

### Note on License Detection

GitHub’s automatic license detection only recognizes the license file in the root directory. Since this project uses multiple licenses for different parts, please consult the `LICENSE` files within each subdirectory to understand the applicable terms.
