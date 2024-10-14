# Conda

Conda is a virtual environment manager for Python. With conda you can create a python
environment with the specific packages and versions you want. You can easily switch
between environment and make configuration files that are easy to share and replicate.
It is also very efficient.

## Example use case:

Currently there is a feature of python that I want to use called type aliasing. This
is a feature only available in python 3.12. I could try and download the latest version
of python but that would be for my entire machine, and I might not want that. So I can
create an environment specifically for the notJSON tool and then install the version
of Python there. It is the same process for downloading packages you want. Then once I
have created a virtual environment with all the necessary software and requirements
installed I can export the environment into a requirements yml file, and then anyone
can use conda to recreate the environment based on the yml file.


### Quick Tutorial

First i'll create a new conda environment:

```
(base) UNIX conda create --name notJSON   
```

Then I will activate the environment and list the packages installed:

```
(notJSON) UNIX conda activate notJSON 
(notJSON) UNIX conda list                                                                                                                    
# packages in environment at /Users/Mikolaj/miniconda3/envs/notJSON:
#
# Name                    Version                   Build  Channel

```

As you can see there is nothing installed. Next I will install python 3.12 and xmltodict
then list the installed packages.

```
(notJSON) UNIX conda install python=3.12
(notJSON) UNIX conda install xmltodict
(notJSON) UNIX conda list
# packages in environment at /Users/Mikolaj/miniconda3/envs/notJSON:
#
# Name                    Version                   Build  Channel
bzip2                     1.0.8                h6c40b1e_6  
ca-certificates           2024.9.24            hecd8cb5_0  
expat                     2.6.3                h6d0c2b6_0  
libcxx                    14.0.6               h9765a3e_0  
libffi                    3.4.4                hecd8cb5_1  
ncurses                   6.4                  hcec6c5f_0  
openssl                   3.0.15               h46256e1_0  
pip                       24.2            py312hecd8cb5_0  
python                    3.12.7               hcd54a6c_0  
readline                  8.2                  hca72f7f_0  
setuptools                75.1.0          py312hecd8cb5_0  
sqlite                    3.45.3               h6c40b1e_0  
tk                        8.6.14               h4d00af3_0  
tzdata                    2024b                h04d1e81_0  
wheel                     0.44.0          py312hecd8cb5_0  
xmltodict                 0.13.0          py312hecd8cb5_0  
xz                        5.4.6                h6c40b1e_1  
zlib                      1.2.13               h4b97444_1  

```

As you can see see it installed xmltodict and a lot of other stuff once python 3.12
was installed

If I want to I can export the specifications for the environemnt to a yml file like so:

```
(notJSON) UNIX conda env export > notJSON_environment.yml                                                                                        
```

Then notJSON_environment.yml will look like this:
```
name: notJSON
channels:
  - defaults
  - conda-forge
dependencies:
  - bzip2=1.0.8=h6c40b1e_6
  - ca-certificates=2024.9.24=hecd8cb5_0
  - expat=2.6.3=h6d0c2b6_0
  - libcxx=14.0.6=h9765a3e_0
  - libffi=3.4.4=hecd8cb5_1
  - ncurses=6.4=hcec6c5f_0
  - openssl=3.0.15=h46256e1_0
  - pip=24.2=py312hecd8cb5_0
  - python=3.12.7=hcd54a6c_0
  - readline=8.2=hca72f7f_0
  - setuptools=75.1.0=py312hecd8cb5_0
  - sqlite=3.45.3=h6c40b1e_0
  - tk=8.6.14=h4d00af3_0
  - tzdata=2024b=h04d1e81_0
  - wheel=0.44.0=py312hecd8cb5_0
  - xmltodict=0.13.0=py312hecd8cb5_0
  - xz=5.4.6=h6c40b1e_1
  - zlib=1.2.13=h4b97444_1
prefix: /Users/Mikolaj/miniconda3/envs/notJSON
```

If I want to create an environment from the yml file I can run the following command:

```
conda env create -f environment.yml
```