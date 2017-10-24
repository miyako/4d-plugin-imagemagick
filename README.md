4d-plugin-imagemagick
=====================

Updated version of [Tech Note: ImageMagick Plug-in](http://kb.4d.com/assetid=43892) by Thomas Maul.

Using [ImageMagick-7](https://www.imagemagick.org/script/index.php) with basic configuration.

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

### Download

[2.1.0](https://github.com/miyako/4d-plugin-imagemagick/releases/tag/2.1.0)

### Related projects

[4d-plugin-gs](https://github.com/miyako/4d-plugin-gs)

### Build Information

* Notable build flags for ``ImageMagick`` on Mac

```
--without-x 
--enable-hdri 
--enable-cipher 
--enable-zero-configuration 
--without-perl 
--without-x 
--with-openexr 
--without-threads 
```

* Notable build flags for ``libgs`` on Mac

```
--without-x 
--disable-threading 
--without-libidn
--disable-cups
```

**Note**: On Mac, need to ``make so`` to build a ``dylib``

https://www.ghostscript.com/doc/9.21/Make.htm#Mac_build

**Issue**: When 4D Server.app is quit (not when the structure is closed), the following error is systematically raised in the client manager thread.

```
_pthread_tsd_cleanup
_pthread_exit
pthread_exit
TSExit
YieldToThread
SetThreadState
```

``pthread`` seems to be used for ``CUPS``; let's __disable it__.

**TODO**: disable threading for imagemagick itself.

### Formats

* Windows Only

CLIPBOARD
EMF
~~EXR~~
FLIF
WEBP
WMF

* Both Platforms

3FR
3G2
3GP
A
AAI
AI
ART
ARW
AVI
AVS
B
BGR
BGRA
BGRO
BMP
BMP2
BMP3
BRF
C
CAL
S
CALS
S
CANVAS
CAPTION
CIN
CIP
CLIP
CMYK
CMYKA
CR2
CRW
CUR
CUT
DCM
DCR
DCX
DDS
DFONT
DNG
DPX
DXT1
DXT5
EPDF
EPI
EPS
EPS2
EPS3
EPSF
EPSI
EPT
EPT2
EPT3
ERF
**EXR**
FAX
FILE
FITS
FRACTAL
FTP
FTS
G
G3
G4
GIF
GIF87
GRADIENT
GRAY
GROUP4
HALD
HDR
HISTOGRAM
HRZ
HTM
HTML
HTTP
HTTPS
ICB
ICO
ICON
IIQ
INFO
INLINE
IPL
ISOBRL
ISOBRL6
J2C
J2K
JNG
JNX
JP2
JPC
JPE
JPEG
JPG
JPM
JPS
JPT
JSON
K
K25
KDC
LABEL
M
M2V
M4V
MAC
MAP
MASK
MAT
MATTE
MEF
MIFF
MKV
MNG
MONO
MOV
MP4
MPC
MPEG
MPG
MRW
MSL
MSVG
MTV
MVG
NEF
NRW
NULL
O
ORF
OTB
OTF
PAL
PALM
PAM
PANGO
PATTERN
PBM
PCD
PCDS
PCL
PCT
PCX
PDB
PDF
PDFA
PEF
PES
PFA
PFB
PFM
PGM
PGX
PICON
PICT
PIX
PJPEG
PLASMA
PNG
PNG00
PNG24
PNG32
PNG48
PNG64
PNG8
PNM
PPM
PS
PS2
PS3
PSB
PSD
PTIF
PWP
R
RADIAL-GRADIENT
RAF
RAS
RAW
RGB
RGBA
RGBO
RGF
RLA
RLE
RMF
RW2
SCR
SCREENSHOT
SCT
SFW
SGI
SHTML
SIX
SIXEL
SPARSE-COLOR
SR2
SRF
STEGANO
SUN
SVG
SVGZ
TEXT
TGA
THUMBNAIL
TIFF
TIFF64
TILE
TIM
TTC
TTF
TXT
UBRL
UBRL6
UIL
UYVY
VDA
VICAR
VID
VIFF
VIPS
VST
WBMP
WMV
WPG
X3F
XBM
XC
XCF
XPM
XPS
XV
Y
YC
YC
YUV

## Syntax

See [Tech Note: ImageMagick Plug-in](https://github.com/miyako/4d-plugin-imagemagick/blob/master/ImageMagick/06-32%20ImageMagick.pdf)

### Example

* Convert PDF to PNG

```
DOCUMENT TO BLOB(System folder(Desktop)+"test.pdf";$PDF)

$im:=IM New Object 
$error:=IM Open Blob ($im;$PDF)
$error:=IM Set Image Properties ($im;IM_Pref_Magick;"PNG")
$error:=IM Save Blob ($im;$PNG)
  //or...
  //$error:=IM Save File($im;System folder(Desktop)+"test.png")
$error:=IM Clear Object ($im)

BLOB TO DOCUMENT(System folder(Desktop)+"test.png";$PNG)
```
