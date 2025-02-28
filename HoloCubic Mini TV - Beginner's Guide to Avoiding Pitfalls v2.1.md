###### <sub>All In One™</sub><br />Zhihui Jun's `HoloCubic` Mini TV<br />──<br /><sup>Beginner's Guide</sup><br />`#Latest Version|V2.1#`<br /><br /><br />**Su Jian Dan Mo, Liu Ma Xiao Ge, Mysterious Treasure Room, Wu Chang Miao Tai, Zui Meng, Dong Xiao Xin, Xiao Er Hei, Romantic Revolution in Southern Anhui, Hui Qian, Yi Ye Zhi Qiu**<br />*Must-read for group navigation*

[TOC]

# Chapter 1  Preface

This document is from the `#HoloCubic AIO Multifunctional Firmware Group 755143193 #(blue)`, and it is a detailed description of the production of `#HoloCubic #(blue)` and `#AIO Firmware (All in One) #(orange)`. Introduction to the transparent mini TV: https://www.bilibili.com/video/BV1jh411a7pV?p=6. If you have any questions, please ask more, be polite, and the group members are all volunteering out of love. `#Note: Read the manual before asking questions #(orange)`

The main content of this document is compiled based on existing materials in the group.

Original author's project link: https://github.com/peng-zhihui/HoloCubic

Group owner's project address: https://github.com/ClimbSnail/HoloCubic_AIO (latest version) or: https://gitee.com/ClimbSnailQ/HoloCubic_AIO

`#Video references: #(red)`

`#Group owner (ClimbSnail Bilibili: Liu Ma Xiao Ge)'s|Video Collection 📝 #(blue)`:

https://www.bilibili.com/video/BV1jh411a7pV/?spm_id_from=333.788.recommend_more_video.0

`#Yi Ye Zhi Qiu's|Nanny-level Tutorial #(blue)`: https://www.bilibili.com/video/BV11h41147iJ?spm_id_from=333.999.0.0

`#Mysterious Treasure Room's|[Production Pit Avoidance] 💡 #(blue)`: https://b23.tv/WuBqTGO

`#Hui Qian's|Soldering Reference Tutorial #(blue)`: https://b23.tv/A83JUGt?share_medium=android&share_source=qq&bbid=BBCEC45F-7A83-45A8-B161-5384DDA3085232266infoc&ts=1651579335471

`#Group member Xue Ding_E_Le Me's|Tutorial Reference #(blue)`: https://www.bilibili.com/video/BV1eu411i7Qo?p=1&share_medium=android&share_plat=android&share_session_id=8f9d7992-dfe1-46c9-84b6-055729c97ae0&share_source=QQ&share_tag=s_i&timestamp=1654861439&unique_k=JUQMGWO

Others to be added...

# Chapter 2  Hardware and Case Production

`#All hardware files involved in Chapter 2 are in the "Hardware and Case Related" group folder|corresponding version compressed package #(yellow)`

## Preparation before hardware production

Install Altium Designer (referred to as "AD", available in the group folder "Developer Tools", can be downloaded by yourself)

Purpose of installation: ① Convenient to open schematics & PCB for viewing when there are problems with soldering

② Pack and send to the board factory (e.g., JLCPCB) to avoid single order suspicion, it is recommended to add or delete some silkscreen. (If you don't know how to modify or generate Gerber files, you can use "HuaQiu DFM" to directly generate Gerber files, the method is in 2.3.2)

![image-20220610202303750](https://pic.imgdb.cn/item/62a337ac0947543129627416.png![Image](xxx.png#center))

`#Install "JLCPCB Order Assistant" - a must for free #(orange)`

Download link (top right corner: download PC assistant): https://www.jlc.com/?s=AD&sdclkid=AL2s152ibJDibOfpA5gD&renqun_youhua=727919&bd_vid=11596835000121341583

![image-20220610202449490](https://pic.imgdb.cn/item/62a338150947543129630ab0.png![Image](xxx.png#center))

## Hardware Versions (Image source from group members)

Zhihui Jun has a total of four versions, the transparent base version Naive, metal, Ironman version, and BiliBili angel base.

Most group members use the transparent base Naive version.

`#①  Transparent base Naive version| (board thickness recommended 1.2mm) #(cyan)`:

![image-20220610203418927](https://pic.imgdb.cn/item/62a33a4f0947543129665b5b.png![Image](xxx.png#center))

`#②  Metal version| (board thickness recommended 1.2mm [transparent Metal2.0 supports 1.6mm, recommended 1.2mm]) #(cyan)`:

<img src="https://pic.imgdb.cn/item/62a33a7009475431296687a3.png![Image](xxx.png#center)" alt="image-20220610203452685" style="zoom:67%;" />

`#③  Ironman version| (Zhihui Jun's source file board thickness recommended 1.0mm) #(cyan)`:

 <img src="https://pic.imgdb.cn/item/62a33af50947543129674a03.png![Image](xxx.png#center)" alt="image-20220610203558203" style="zoom:80%;" />

`#④ BiliBili angel version| none #(cyan)`

 <img src="https://pic.imgdb.cn/item/62a33afc09475431296753fa.png![Image](xxx.png#center)" alt="image-20220610203621211" style="zoom:80%;" />

Most group members use the transparent base Naive version, of course, the group owner also made a lot of metal Metal versions. Some group members made the Ironman head version (as shown in Figure 2.2).

 ![image-20220610203652890](https://pic.imgdb.cn/item/62a33b020947543129675d06.png![Image](xxx.png#center))

                                                                                                                              Figure 2.2

Many experts have written Holocubic firmware, and the firmware of each version is basically universal (Metal, Naive) for these two hardware versions (at least the group owner's AIO firmware is fully compatible).

Choose the version you like. Some circuits of the original author Zhihui Jun's Holocubic have timing issues (`#need to change the C7 capacitor to 1uF~10uF to solve #(orange)`), and there are improved versions in the group (`#be sure to check the latest version in the group files #(orange)`).

Note:

**①** `#The hardware only supports 2.4G wifi. #(yellow)` 5G and dual-band are not supported. No firmware can break the hardware limitations.

**②** `#For non-science/engineering majors, no electronic foundation, average hands-on ability, and want to play #(yellow)`, it is recommended to ask group members, some group members have finished products for transfer or sale (`#The cost of making it yourself is about 200, please be cautious #(yellow)`).

**③** Be sure to ask group members if you are unsure about purchasing components!!!

**④** `#New DC-DC (metal) version, LDO (LP2992 or ME6211C33), DCDC (MP1471) choose one [if MP1471 is soldered, the LDOs on the expansion board and mainboard must be removed]. #(yellow)`

**⑤** Metal, Naive compatibility needs to check the latest ( `#version packages in the group #(yellow)`)

## PCB Production

### File Download and Instructions

`#Step 1 #(orange)`: After learning and understanding the group materials through 2.2 `#confirm the hardware version #(yellow)`, find the corresponding PCB file in the AIO group files and download it (the group files will be updated periodically, old files will be removed).

`#Note: The group files have been tested and improved by the group owner #(red)`

![image-20220610212836190](https://pic.imgdb.cn/item/62a3e6130947543129190deb.png![Image](xxx.png#center))

![image-20220610212850946](https://pic.imgdb.cn/item/62a3e6260947543129191ed2.png![Image](xxx.png#center))

                                                                                                                   `#2.3.1|File Download #(lime)` 

`#Step 2 #(orange)`: After downloading, unzip it, and five files will appear as shown in Figure 2.3.2. Take the Metal version as an example.

![image-20220610213015473](https://pic.imgdb.cn/item/62a3e63f0947543129193380.png![Image](xxx.png#center))

                                                                                                                    `#2.3.2|Unzip Files #(lime)` 

![image-20220610213035457](https://pic.imgdb.cn/item/62a4025c094754312935287f.png![Image](xxx.png#center))

![image-20220610213044184](https://pic.imgdb.cn/item/62a4026e0947543129353d31.png![Image](xxx.png#center))

                                                                                                           `#2.3.3|Mainboard Folder File Description #(lime)`

![image-20220610213100688](https://pic.imgdb.cn/item/62a4028b0947543129355f73.png![Image](xxx.png#center))

![image-20220610213107948](https://pic.imgdb.cn/item/62a402990947543129356d76.png![Image](xxx.png#center))

                                                                                                      `#2.3.4|Expansion Board Folder File Description #(lime)`

### PCB Sample Production Tutorial

`#Note: Be sure to modify the silkscreen before placing an order #(orange)`, adding or deleting silkscreen is fine, then compress the PCB file and send it to JLCPCB. If you don't know how to generate Gerber files, you can download a "HuaQiu DFM" software.

![image-20220610213219026](https://pic.imgdb.cn/item/62a3e67c0947543129196627.png![Image](xxx.png#center))

                                                                                                             `#Figure shows AD09 adding silkscreen #(lime)`

#### How to use HuaQiu DFM to generate Gerber

HuaQiu DFM download link: https://dfm.elecfans.com/index

Cloud disk download link: https://www.aliyundrive.com/s/vh9fgUf57jz

`#①  Common Gerber File List #(purple)`

When making PCB boards, the Gerber files handed over to the board factory must include the following 1-10 and 15, 11-14 can be omitted, but it is recommended to include them in the Gerber file.

1. GTO (Top Overlay): Top layer silkscreen, commonly white oil.

2. GTS (Top Solder): Top layer solder mask, commonly green oil.

3. GTL (Top Layer): Top layer routing.

4. Gtp (Top Paste Mask): Top layer solder paste mask.

5. GBp (Bottom Paste Mask): Bottom layer solder paste mask.

6. GBL (Bottom Layer): Bottom layer routing.

7. GBS (Bottom Solder): Bottom layer solder mask, commonly green oil.

8. GBO (Bottom Overlay): Bottom layer silkscreen, commonly white oil.

9. GMx (Mechanical) or GKO (Keep-out Layer): Used to define the board outline, select the layer where the board outline is located.

10. Gx (Mid Layer): Middle signal layer, there are as many files as there are middle layers.

11. Gd (Drill Drawing): Drill drawing layer.

12. Gg (Drill Guide): Drill guide layer.

13. Gpt (Top Pad Master): Top layer pad.

14. Gpb (Bottom Pad Master): Bottom layer pad.

15. NC drill Files: Drill files, AD export is generally a txt file. Generally, there are the following files: ① RoundHoles-NonPlated (round hole non-plated drill file) ② RoundHoles-Plated (round hole plated drill file) ③ SlotHoles-Plated (slot hole plated drill file).

`#②  Gerber File Explanation #(purple)`

1. Top Overlay/Bottom Overlay: Top and bottom layer silkscreen, mainly showing component outlines, reference designators, attributes, annotation information, etc.

2. Top Solder/Bottom Solder: Top and bottom layer solder mask, showing pads, openings, components, etc. that do not need to be covered with green oil.

3. Top Layer/Bottom Layer: Top and bottom layer routing, top and bottom layer routing information.

4. Mechanical or Keep-out Layer: Used to place mechanical graphics, such as PCB outlines, etc. The graphics placed on this layer will have corresponding graphics on any layer and will not be silkscreened with solder mask. Generally used to place the board outline.

5. Top Paste Mask/Bottom Paste Mask: These two layers are used to make stencils.

6. Drill Drawing, Drill Guide, NC drill Files are all drill information. What are their functions? Why do we need to export NC Drill Files after exporting Gerber files?

① Drill Guide is mainly used to guide drilling, mainly for manual drilling positioning.

② Drill Drawing is used to view drill hole diameters. These two files are used together for manual drilling. However, most are now CNC drilling, so these two layers are not very useful. We need to provide NC drill Files (generally txt or excel files) for CNC drilling. Although Drill Drawing and Drill Guide files can be generated from NC drill Files, it is recommended to include these two files in the Gerber file to reduce subsequent work.

`#Step 1 #(yellow)`: Open HuaQiu DFM, it will prompt you to register/login (I haven't tried not logging in, mine is auto-login), after registering/logging in, click File → Open → PCB (need to generate Gerber files)

![image-20220610213545135](https://pic.imgdb.cn/item/62a4048a0947543129379f71.png![Image](xxx.png#center))

                                                                                                                            `# Import PCB #(lime)`

![image-20220610213611294](https://pic.imgdb.cn/item/62a404a1094754312937b627.png![Image](xxx.png#center))

                                                                                                                       `# Importing #(lime)`                   

`#Step 2 #(yellow)`: After opening, you will see the Gerber files as shown below

![image-20220610213634982](https://pic.imgdb.cn/item/62a404b7094754312937ce42.png![Image](xxx.png#center))

![image-20220610213642912](https://pic.imgdb.cn/item/62a404ca094754312937e2ac.png![Image](xxx.png#center))

`#Step 3 #(yellow)`: Select File, Export Gerber Files, choose the folder to export to. After exporting, it will prompt that the export is successful.

![image-20220610213700360](https://pic.imgdb.cn/item/62a404d7094754312937f1d6.png![Image](xxx.png#center))

![image-20220610213709034](https://pic.imgdb.cn/item/62a404fd0947543129381f79.png![Image](xxx.png#center))

![image-20220610213716614](https://pic.imgdb.cn/item/62a405290947543129384e4f.png![Image](xxx.png#center))

`#Step 4 #(yellow)`: In the exported files, check the Gerber files to confirm, then compress and package them.

![image-20220610213732789](https://pic.imgdb.cn/item/62a4051109475431293834bc.png![Image](xxx.png#center))

`#Step 5 #(yellow)`: Compare the exported Gerber files with the list above to see if there are any missing or extra files.

![image-20220610213749660](https://pic.imgdb.cn/item/62a40564094754312938a2af.png![Image](xxx.png#center))

#### JLCPCB Sample Production (Refer to the Naive version Holo3 production tutorial by the group admin)

`#Step 1 #(yellow)`: Compress the mainboard PCB file & expansion board PCB & Gerber files marked in 2.2.2 separately.

![image-20220610213818292](https://pic.imgdb.cn/item/62a40590094754312938cc07.png![Image](xxx.png#center))

`#Step 2 #(yellow)`: Upload the PCB compressed file to the JLCPCB order software, and wait patiently for the parsing process.

![image-20220610213839623](https://pic.imgdb.cn/item/62a405ef0947543129393716.png![Image](xxx.png#center))

                                                                                                                        `# Upload PCB File #(lime)`

![image-20220610213854642](https://pic.imgdb.cn/item/62a406250947543129397cdb.png![Image](xxx.png#center))

                                                                                                                            `#  PCB File Parsing #(lime)`  

`#Step 3 #(yellow)`: After parsing is complete, the order options will appear as shown below. The length and width of the board are generally automatically recognized. If it cannot be automatically recognized, you can fill in any value, such as 5x5, etc. The board factory will adjust it later. The number of boards is 5 (more than that cannot be free).

![image-20220610213917796](https://pic.imgdb.cn/item/62a4062e0947543129398733.png![Image](xxx.png#center))

`#Step 4 #(yellow)`: The board thickness is determined based on the version of the mini TV you choose.

![image-20220610213934524](https://pic.imgdb.cn/item/62a406350947543129398fca.png![Image](xxx.png#center))

                                                                                                                        `#  Board Thickness Selection #(lime)`

`#Step 5 #(yellow)`: The color of the solder mask can be chosen according to your preference.

![image-20220610213949548](https://pic.imgdb.cn/item/62a4063c094754312939981a.png![Image](xxx.png#center))

                                                                                                                     `#  Solder Mask Color Selection #(lime)`   

`#Step 6 #(yellow)`: Whether to open the stencil file.

Note: It is recommended for beginners to open the mainboard's front stencil. The group will provide the stencil file, and you can find a stencil seller on Taobao, priced at 10~20 (excluding shipping).

![image-20220610214027440](https://pic.imgdb.cn/item/62a406430947543129399ed7.png![Image](xxx.png#center))

                                                                                                                    `#  Stencil File #(lime)`    

## Material and Tool Purchase

### Component Purchase (Refer to the BOM table in the AIO group online document)

**①** The file contains a BOM, and you can purchase components based on the BOM (recommended to buy from Taobao Yuxin Electronics). MPU 6050 can be purchased as a module and disassembled. You can also refer to the recommended links in the group online document https://docs.qq.com/sheet/DQUpSbmN4TVNha0h0

**②** The screen can be purchased from Taobao Zhongjingyuan (brand Hancai [currently the best display effect])

**③** If you don't know or are unsure, you can ask group members.

**④** The voltage rating of capacitors/resistors should be ≥5V (e.g., 16V, 24V, 50V, etc.) [only for this project]

**⑤** The connector socket model is: flip-down 8P (used for both the expansion board and the mainboard), buy the same direction 0.5 * 8P (Naive recommends 6cm, Metal uses 3cm).

**⑥** Zhihui Jun's original card slot model is DM3D-SF (not recommended), the modified card slot can be found in the group online document link or search for flip-down internal welding TF card slot (8P) on Taobao.

**⑦** When purchasing LDO, be sure to pay attention to the model, ME6211C33 [the 33 at the end indicates 3.3V], don't buy the wrong one. Some group members bought the wrong one.

Note: Some components are recommended to buy 1-2 more, the flip-down 8P socket is recommended to buy about 6-8.

<img src="https://pic.imgdb.cn/item/62a4064a094754312939a75c.png![Image](xxx.png#center)" alt="image-20220610214236590" style="zoom:67%;" />

**⑦** Memory card selection

The firmware has certain compatibility issues with memory cards, not all are compatible. Currently supports `#SD, SDHC types of memory cards, does not support SDXC! #(orange)` Recommended memory cards that have been verified.

①  Patriot 32G ordinary card. About 20 yuan on Taobao. (High cost performance, recommended)

②  SanDisk 32G ordinary card. About 30 yuan on Taobao.

⑧ Screen issues

Screen specifications: 1.3 inches, driver ST7789, resolution 240*240, soldered 12Pin. Most screen boards have a metal shell, `#pay attention to short circuit issues! #(orange)`

There are many such screens online, but for making Holocubic, you need to choose carefully, as the screen will affect the overall display effect. After testing many screens, the best effect is from Zhongjingyuan.

Other screens are not recommended for making Holocubic. Below is an actual comparison (please ignore the background difference):

Left: Zhongjingyuan (Hancai)  Right: Youzhijing

![image-20220611203259749](https://pic.imgdb.cn/item/62a48b7f0947543129e84767.png![Image](xxx.png#center))  

The difference between the two screens after applying the prism is mainly that the blank area around the Youzhijing display is seriously blue, which greatly affects the final effect. The blank area of the Zhongjingyuan display is very clean. Note: In fact, the base color of Zhongjingyuan is also slightly blue, but very light.

Regarding brightness issues (unrelated to the screen):

The above picture also shows that the left side is significantly brighter because the factory polarizer protective film on the left side has not been removed (which can increase brightness), and the color on the left side becomes extremely inaccurate due to the refraction of the protective film.

Those who have done experiments will also find that after removing the protective film, the brightness of the prism placed on the X-axis and Y-axis is different. The human eye is more sensitive to color than brightness, so it is recommended to remove the protective film. (`#Brightness can be improved by purchasing a 6:4 prism, the brightness of 6:4 is slightly higher than 5:5 #(orange)`)

Of course, if you care more about brightness, you can choose not to remove the protective film. When buying the screen, you can ask the seller to ship it with the protective film and not to stick the green label on the protective film.

### Production Tools (Refer to the group owner)

`#①|Soldering Tools #(orange)` 

Soldering iron (936 soldering station, cost-effective, many types of soldering iron tips);

Soldering station, also known as: iron plate (500w Deer Fairy);

Tweezers (0402 size is small, recommended to use pointed tweezers);

Solder wire (0.3mm/0.5mm/1.0mm DIY commonly used are these three specifications),

Flux and solder paste are recommended to buy from repairers (if conditions permit, you can buy Japanese brands from Amazon).

`#②|Sandpaper #(orange)`

300 grit, 800 grit, 5000 grit, 8000 grit, buy according to demand (the larger the number, the finer the grinding)

High-transparency case is a frosted case, polished with fine sandpaper and sprayed with light oil.

`#The group owner recommends 400 and 800 grit, coarse grinding + fine grinding 800 grit can produce a frosted effect, and grinding needs to be done under running water, otherwise, the light will show scratches. #(yellow)`

`#③|Glue (refer to the group owner's tutorial) #(orange)`

704 glue (used to seal the gap around the screen), UV glue or B-7000 [used to stick the screen] Note: UV glue requires an additional curing lamp. Prism bonding video tutorial https://www.bilibili.com/video/BV1jh411a7pV?p=5

### Case Production

Pure white can be ordered from Sanwei Monkey (JLCPCB)

Semi-transparent can be ordered from Future Factory or Taobao (you can also consult group members)

Metal CNC (the car has already left) [you can wait for the group owner's Ironman car]

## 3D Printing of the Case

`#All the latest model files are in the corresponding version compressed package in the group!!! #(yellow)`

`#①|Naive Transparent Base (Improved Version) #(orange)`  

1. Suitable for Naive version hardware.

2. The original design scheme uses screws to connect the upper and lower shells, but there is an improved version with magnetic attraction in the group (the magnet is a 3*3mm round magnet), it is recommended to use the improved version.

3. The base is made with a 3D printer, it is recommended to use a semi-transparent printing effect.

4. If you want to make the printed surface frosted, it is recommended to use 800 grit sandpaper to polish it under running water.

5. If you are looking for online printing, pay attention to the tolerance, if the case is too small, the mainboard will not fit.

6. Mainboard thickness 1.2mm (using the improved version case). Expansion board thickness 1.2mm.

`#②|Metal Base (Improved Version) #(orange)`

1. Suitable for Metal version hardware.

2. The base is made with a 3D printer, it is recommended to use a semi-transparent printing effect.

3. If you want to make the printed surface frosted, it is recommended to use 800 grit sandpaper to polish it under running water.

4. Both v1.0 and v2.0 versions are modified based on Zhihui Jun's original version, with an internal memory card slot at the bottom.

5. Both v1.0 and v2.0 are compatible with all versions of the mainboard and expansion board in this folder. It is recommended to use 1.2mm thick PCB boards (mainboard and screen board).

`#V 1.0's left and right reinforcement seats are too large, V2.0 optimizes this defect. #(yellow)`

`#③|Ironman Base #(orange)`

1. Suitable for Ironman version hardware.

2. Zhihui Jun's original base recommends: mainboard thickness 1.0mm. Expansion board thickness 1.0mm.

`#④|BiliBili #(orange)`

No base yet. (see group files)

`#⑤|Ironman Head #(orange)`

No base yet. Open source address: https://gitee.com/qlexcel/holo-iron-man

## Using and Making Dynamic BOM

### Using Dynamic BOM

`#Step 1 #(yellow)`: Open the soldering diagram file marked in 2.2.2

![image-20220610214348237](https://pic.imgdb.cn/item/62a40655094754312939b2d0.png![Image](xxx.png#center))

                                                                                                                               `#  Open Soldering Silkscreen Diagram File #(lime)`

`#Step 2 #(yellow)`: Click on the component on the left with the mouse, it will display specific content (the same components will also be highlighted)

![image-20220610214411109](https://pic.imgdb.cn/item/62a4065a094754312939b798.png![Image](xxx.png#center))

`#Step 3 #(yellow)`: If you want to see the first pin of the component, you can set it in the upper right corner

![image-20220610214431618](https://pic.imgdb.cn/item/62a40661094754312939be18.png![Image](xxx.png#center))

### Making Dynamic BOM

![image-20220610214454029](https://pic.imgdb.cn/item/62a4066a094754312939c9ae.png![Image](xxx.png#center))

![image-20220610214510405](https://pic.imgdb.cn/item/62a40670094754312939cf4a.png![Image](xxx.png#center))

Note: AD script link for making dynamic BOM: https://github.com/lianlian33/InteractiveHtmlBomForAD

If it doesn't open, you can download it from the cloud disk: https://www.aliyundrive.com/s/f6VVYfwsQ3S

Or in the group file "Developer Tools" inside "InteractiveHtmlBomForAD"

## Improved Expansion Board Introduction

`#V 1.5 #(orange)`

1. Improved expansion board, added 662k 3.3v 300ma voltage regulator chip (shares the screen current, reducing the device restart caused by insufficient power supply of the mainboard 2992 voltage regulator chip);

2. The expansion board is also suitable for MetalV2.0 case

![image-20220610214555211](https://pic.imgdb.cn/item/62a40677094754312939d797.png![Image](xxx.png#center))

![image-20220610214602286](https://pic.imgdb.cn/item/62a4067c094754312939dd3a.png![Image](xxx.png#center))

`#V 2.0 #(orange)`

1. Improved expansion board, added MP1471 power management chip (reduces the device restart and heating issues caused by insufficient power supply of the mainboard LP2992 or ME6211 voltage regulator chip);

2. The expansion board is suitable for MetalV2.0 case, Naïve needs to modify the mold

![image-20220610214704307](https://pic.imgdb.cn/item/62a40681094754312939e153.png![Image](xxx.png#center))

## Soldering PCB to PCBA

Note: Refer to the group file "Some Troubleshooting Methods for Main Control Board Soldering Issues"

Since the components on the main control board are 0402 packages, it is somewhat difficult for non-science/engineering majors, no electronic foundation, average hands-on ability, and no soldering experience. The difficulty level depends on your "skills".

Generally, soldering is done in the order of component size, from small to large. It is recommended to use a desoldering station or hot air gun, not just a soldering iron. If you have never soldered anything, or only done electronic and electrical practice, it is recommended to buy a heating station. There is a 20 yuan Deer Fairy desoldering station on Taobao (the usage method of the soldering station can be found on Bilibili). This is completely sufficient (of course, if you are rich, you can get a hot air gun and soldering station combination), and then use a soldering iron.

All components on the back of the main control board (SD card slot and 4 resistors) do not affect the normal use of the board if not soldered. It is recommended to solder them after testing the screen.

Regarding the difficulty of applying solder: for those who don't know anything, it is recommended to get a stencil on Taobao. For those who have never done it, it is recommended to use the stencil in the group file. After applying solder paste with the stencil (medium temperature solder paste is fine, buy a small can of 30 grams, it can be used for a long time, 20 yuan on Pinduoduo), place the components according to the position in the group soldering reference diagram, and put it on the heating station to heat. During the soldering process, the position of the components may shift, use tweezers to adjust the position.

(Note: When soldering the esp32, place the chip in position, after the solder melts, turn off the heating station switch, and press the chip with tweezers while cooling)

PS: C7 capacitor can be 1uF~10uF. (Especially for those bought from "Geek ***" on Taobao, pay attention)

#### Main Control Board PCB Soldering Begins

`#①|Ensure the computer port can recognize [measure the power and ground for short circuit before powering on] #(yellow)`

`#Step 1 #(yellow)`: Solder the LDO and surrounding resistors and capacitors

Resistors, capacitors, transistors (VT1-2, 8050), voltage regulator chip (LP2992) are soldered first, the antenna (A1) and LED (D1) can be soldered last.

![image-20220610214819180](https://pic.imgdb.cn/item/62a4068c094754312939ecac.png![Image](xxx.png#center))

`#Step 2 #(yellow)`: Solder CP2102 and Type C interface

After the first step is completed, prepare to solder CP2102 (U1) and Type C interface. If there is no problem with this part of the soldering, the board can be recognized by the computer (measure the VCC (5V) and GND for short circuit before plugging into the computer), and the device manager will recognize the serial port.

![image-20220610214835779](https://pic.imgdb.cn/item/62a40691094754312939f2c7.png![Image](xxx.png#center))

Note: Soldering direction - chip dot to PCB white

![image-20220610214852463](https://pic.imgdb.cn/item/62a40696094754312939f847.png![Image](xxx.png#center))

`#②|Common soldering issues in this part #(yellow)`:

`#Ⅰ|No response after plugging into the computer #(cyan)`

Most likely a cold solder joint, first check with the naked eye or a magnifying glass for any solder bridges, then check the voltage of the LP2992 (ME6211) pins with a multimeter in DC voltage mode (do not use ohm mode, it will damage the multimeter) to see if there is 5V and 3.3V, then check CP2102 and Type C, and R1 resistor to see if they are soldered properly, press with tweezers.

`#Note: Do not use a data cable that only charges, it must be able to transfer data #(yellow)`

`#Ⅱ|Computer prompts USB port has abnormal current after plugging in #(cyan)`

<img src="https://pic.imgdb.cn/item/62a4069c094754312939fda8.png![Image](xxx.png#center)" alt="image-20220610214915062" style="zoom:67%;" />

The board's VCC and GND are short-circuited or the LDO is damaged. (To avoid unexpected losses, it is recommended to measure the power [5V & 3V3] and ground [GND] for short circuit before powering on)

`#Solution #(orange)`: Check the board, re-solder or replace the LDO

`#Ⅲ|CP2102 is recognized by the computer, but there is a yellow exclamation mark #(cyan)`

`#Solution #(orange)`: The driver is not installed, the driver is in the group file, download and install the driver.

`#Ⅳ|Others #(cyan)`

It may still be a cold solder joint or the direction is wrong or the chip is damaged, check the voltage of the 2992 pins to see if there is 5V and 3.3V, then check CP2102 and Type C.

`#Solution #(orange)`: Check for cold solder joints or Type-C socket issues

`#Ⅴ|CP2102 driver is modified #(cyan)`

`#Solution #(orange)`:

![image-20220610215014567](https://pic.imgdb.cn/item/62a406a109475431293a047d.png![Image](xxx.png#center))

![image-20220610215021227](https://pic.imgdb.cn/item/62a406a709475431293a0ab6.png![Image](xxx.png#center))

![image-20220610215027585](https://pic.imgdb.cn/item/62a406b609475431293a20f6.png![Image](xxx.png#center))

`#③|Ensure ESP32 can communicate with the serial port normally #(yellow)`

`#Step 3 #(yellow)`: Solder the esp32 (U4) chip

![image-20220610215040004](https://pic.imgdb.cn/item/62a406be09475431293a2950.png![Image](xxx.png#center))

Note: ESP32 soldering direction - chip dot to PCB slanted edge

After the serial port is fine, start soldering the ESP32, which should be the most difficult chip to solder on the board. Sometimes after soldering, the ESP32 chip can work normally, and the program can be burned, the blink LED can flash normally, but it does not mean that your soldering is fine, there may still be some IO pins short-circuited or cold soldered, causing the screen not to light up or display issues, or even MPU6050 not working properly, etc.

Note:

**①**  The TF card slot and four 10K pull-up resistors on the back do not affect burning and use.

**②**  Please synchronize the firmware burning with the latest firmware in the group file, try not to use "ancient" firmware

**③**  Successfully burning the firmware may not necessarily light up the LED (it may be a cold solder joint or the LED is damaged), but if the firmware is not successfully burned, the LED will definitely not light up.

Your computer communicates with the ESP32 through USB →Type C→CP2102→ESP32 to burn the program. Any communication failure in the middle will cause the firmware burning to fail.

After soldering, you can first use the upper computer to check if there is any serial port information printed, `#the baud rate for checking the serial port print is 115200 #(yellow)` (baud rate: 115200 [not 1152000, nor 921600 (use 921600 for downloading, of course, 115200 can also be used, just slower)]), if there is no problem with the soldering (only indicates that the serial port can communicate with the ESP32 normally, does not mean other IO ports are fine), there will be serial port information, if there is a cold solder joint, there will be none.

`#If the soldering is normal, the voltage of the two 8050 collector pins, that is, the top pin, is about 3.3V. #(yellow)`

![image-20220610215100448](https://pic.imgdb.cn/item/62a406c309475431293a2ef1.png![Image](xxx.png#center))

Regarding the rst: and boot: related explanations, see Chapter 5, ESP32 Basics.

`#④|Common soldering issues in this part #(yellow)` 

`#Ⅰ|Unable to burn after plugging into the computer #(cyan)`

The upper computer is stuck at the last bit & using VS Code to burn prompts connect ESP 32 time out ...---...----...---- This situation is mostly due to a cold solder joint of the ESP32, any connection failure, or flash error, is due to a cold solder joint of the ESP32 chip, re-solder, too much solder (causing pin bridging) or too little solder (not soldered) will cause this problem, use tweezers, flux, solder wick, and desoldering station flexibly.

`#Solution #(orange)`: Add solder, you can refer to the video on the homepage. (If it works or succeeds, remember to give them a like, comment, and subscribe 😁)

![image-20220610215119591](https://pic.imgdb.cn/item/62a406d309475431293a3e6c.png![Image](xxx.png#center))

`#Ⅱ|C7 capacitor is 0.1uF #(cyan)`  

Zhihui Jun's original file uses 0.1uF, so those who use Zhihui Jun's source file to make the board, the C7 capacitor is basically 0.1uF. If the C7 capacitor is 0.1uF, and the program fails to download during the download process, but the program can be downloaded normally after shorting the ESP32's GPIO0 pin, it is recommended to change the C7 capacitor to 1uF~10uF.

`#Solution #(orange)`: Change the C7 capacitor to 1uF~10uF.

![image-20220610215133241](https://pic.imgdb.cn/item/62a406da09475431293a4694.png![Image](xxx.png#center))

`#Ⅲ|Others #(cyan)` 

It may also be that the CP2102 chip and R3 resistor are not soldered properly, or the two transistors, or the four small components next to U2...

`#Solution #(orange)`: Re-solder the components and try again.

`#Ⅳ |Always restarting after burning #(cyan)`  

It may be that other pins of the ESP32 are cold soldered or bridged, causing it to keep restarting. Being able to burn and read the serial port only means that the burning pins are fine, it does not mean that other pins of the ESP32 are fine.

![image-20220610215159437](https://pic.imgdb.cn/item/62a406ec09475431293a5b22.png![Image](xxx.png#center))

`#Solution #(orange)`: Add solder, use tweezers to move and press lightly to squeeze out the excess solder inside.

![image-20220610215149636](https://pic.imgdb.cn/item/62a406e109475431293a4e1e.png![Image](xxx.png#center))

`#⑤|Unfinished parts on the front of the main control board #(yellow)` 

`#Step 4 #(yellow)`: Solder the remaining components on the front

If your ESP32 can burn the program normally, then you are only 50% away from success.

MPU6050, FPC 8P socket, RGB LED, 2.4G antenna, light sensor (can be omitted)

![image-20220610215216982](https://pic.imgdb.cn/item/62a406f809475431293a6a01.png![Image](xxx.png#center))

Note: MPU 6050 soldering direction - dot to white dot; 2.4G antenna dot to horizontal bar; light sensor AA to white dot.

`#⑥|Common issues in this part #(yellow)`:

`#Ⅰ |APP switches by itself #(cyan)`

(1) Not initialized after powering on

`#Solution #(orange)`: Power off and place horizontally, wait for MPU 6050 to initialize (LED starts to change)

(2) Cold solder joint

If your MPU6050 has a cold solder joint, burning the test firmware in the group will always be stuck at the MPU6050 initialization, making you start to doubt life, whether your ESP32 chip is broken again.

`#Solution #(orange)`: Re-solder. (You can refer to the video of the mysterious treasure room)

(3) Bypass capacitor of MPU 6050

Some group members have issues with the capacitor near the MPU 6050 being wrong or cold soldered.

`#Solution #(orange)`: Add solder to MPU 6050 (if adding solder doesn't work, try adding solder to the two pins at the bottom right of the ESP 32) and the nearby capacitors (or directly replace and re-solder).

![image-20220610215235637](https://pic.imgdb.cn/item/62a4070109475431293a73d1.png![Image](xxx.png#center))

`#Ⅱ |Bought fake MPU6050 & broken #(cyan)`

If the serial port information shows MPU 6050 always reporting ******, 80% chance it is broken or 20% chance it is a cold solder joint.

![image-20220610215257158](https://pic.imgdb.cn/item/62a4070a09475431293a7ea3.png![Image](xxx.png#center))

`#Solution #(orange)`: Replace with a new MPU 6050 or add solder (80% chance the chip is broken, 20% chance it is a cold solder joint).

`#Ⅲ |Light sensor soldering issue #(cyan)` 

If the serial port information shows MPU 6050 reporting

[E][esp32-hal-i2c.c:1434]i2cCheckLineState(): Bus Invalid State, TwoWire() Can't init sda=1, scl=0

`#Solution #(orange)`: Confirm if the light sensor is soldered correctly or remove the light sensor and re-solder the MPU 6050. (PS: Some group members have this issue because the light sensor is soldered in the wrong direction)

Below is for reference after soldering

![image-20220610215315275](https://pic.imgdb.cn/item/62a4070e09475431293a83d9.png![Image](xxx.png#center))

#### Expansion Board PCB Soldering Begins

The expansion board is not difficult, just solder the screen, FFC, and MOSFET according to the material list and PCB. Note that there are two versions of the expansion board, one is the original version (not recommended), and the other is the optimized version (recommended to use the latest DC-DC expansion board from the group owner [full version], ME 6211 + 622K optimized version [reduced version]).

When soldering the screen ribbon cable, it is best not to use a desoldering station, just use a soldering iron, apply a little solder paste, otherwise, it is easy to burn the screen.

![image-20220610215342877](https://pic.imgdb.cn/item/62a40681094754312939e153.png![Image](xxx.png#center))

MP1471 soldering direction is horizontal line down

Common issues in this part

The screen board only has backlight

Please measure the reference voltage in the group file and check step by step.

![image-20220610215401098](https://pic.imgdb.cn/item/62a4071d09475431293a921c.png![Image](xxx.png#center))

![image-20220610215408851](https://pic.imgdb.cn/item/62a4072409475431293a9a2f.png![Image](xxx.png#center))

The socket soldering must be careful!!!

![image-20220610214236590](https://pic.imgdb.cn/item/62a4064a094754312939a75c.png![Image](xxx.png#center))

# Chapter 3  Upper Computer Related Issues

## Upper Computer Display Incomplete

Issue: Windows 11 or Windows 10 may display the upper computer as shown below

Solution: Adjust the scaling ratio in the computer resolution interface. Then reopen the upper computer, if there is no change, restart the computer and try again.

![image-20220610215502037](https://pic.imgdb.cn/item/62a4073009475431293aa7cf.png![Image](xxx.png#center))

## Upper Computer Serial Port Information

### MPU 6050 Initialization Failed

Issue: MPU 6050 initialization failed or not connected

Solution: MPU 6050 has a cold solder joint, add solder to the position mentioned above in the mainboard soldering.

![image-20220610215530444](https://pic.imgdb.cn/item/62a4073709475431293ab037.png![Image](xxx.png#center))

### TF Card Cannot Be Read (TF Card Slot Voltage Diagram)

Issue: TF card cannot be read normally or cannot be recognized after a period of time.

![image-20220610215549378](https://pic.imgdb.cn/item/62a4073b09475431293ab507.png![Image](xxx.png#center))

![image-20220610215556324](https://pic.imgdb.cn/item/62a4074109475431293abb3e.png![Image](xxx.png#center))

Solution: First confirm if it is a memory card (TF card, note: TF card supports up to 32G) issue, if not, it may be a cold solder joint issue, as shown below, it may be a resistor or a specific pin of the ESP32 that has a cold solder joint, add solder!

![image-20220610215610255](https://pic.imgdb.cn/item/62a4074609475431293ac050.png![Image](xxx.png#center))

### Unable to Burn

Issue: Unable to erase, progress bar stuck at the last bit, no serial port information (baud rate: 115200 [not 1152000, nor 921600 (use 921600 for downloading, of course, 115200 can also be used, just slower)])

Solution: ESP 32 has a cold solder joint, add solder. (Zhihui Jun's original version, please change the C7 capacitor to 1-10uF) Refer to the mainboard soldering above.

![image-20220610215629658](https://pic.imgdb.cn/item/62a406d309475431293a3e6c.png![Image](xxx.png#center))

# Chapter 4  How to Use a Multimeter

<img src="https://pic.imgdb.cn/item/62a4075609475431293ad29a.png![Image](xxx.png#center)" alt="image-20220610215653753" style="zoom:80%;" />

Taking Fluke as an example, as shown in the picture above, the outer ring of the multimeter is generally divided into six parts: AC current range (A~), DC current range (A-), AC voltage range (V~), DC voltage range (V-), resistance range (Ω), buzzer range (🔈 symbol I can't type, see the picture).

## Measuring Voltage (Taking the mini TV mainboard as an example) [must be in DC voltage range]

①  Set the multimeter to DC range (choose the appropriate range if there are ranges, generally from large to small)

②  One probe of the digital multimeter is connected to the ground, and the other is connected to the pin or pad to be measured (as shown in the picture, one probe is placed on the Type-C, and the other probe is placed on the 5V pin of the LDO).

Note: Be sure to pay attention to the positive and negative poles of the pointer multimeter to avoid damage to the multimeter.

![image-20220610215717268](https://pic.imgdb.cn/item/62a4075b09475431293ad994.png![Image](xxx.png#center))

## Measuring Continuity (Taking the mini TV mainboard as an example) [must be powered off]

①  Set the multimeter to the buzzer range (test for short circuit or continuity)

②  If the power (VCC) and ground (GND) of the mini TV are short-circuited (one probe is placed on GND, and the other probe is placed on 5V or 3V3), if there is a buzzer sound, it indicates a short circuit (continuity), otherwise, there is none. If checking whether the component is damaged (such as resistors, capacitors, etc.), place the two probes on both ends of the component, if there is a buzzer sound, it indicates it is damaged (except for 0Ω), otherwise, there is none.

![image-20220610215736025](https://pic.imgdb.cn/item/62a4076109475431293adfee.png![Image](xxx.png#center))

# Chapter 5  ESP32 Basics: rst cause and boot mode during startup

When the ESP32 starts, the ROM CODE will read the GPIO status and rst cause status to determine the ESP32 working mode.

Understanding and mastering rst cause and boot mode helps to locate certain system issues.

For example:

When the ESP32 starts, it will print the following:

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)

The ROM CODE baud rate is 115200

System reset introduction and rst cause during ESP32 startup

System reset introduction

The system provides three levels of reset methods: CPU reset, core reset, and system reset.

All resets do not affect the data in MEM. The figure shows the structure of the entire subsystem and each reset method:

![image-20220610215813843](https://pic.imgdb.cn/item/62a4076609475431293ae56c.png![Image](xxx.png#center))

CPU reset: only resets all registers of the CPU.

Core reset: resets all digital registers except RTC, including CPU, all peripherals, and digital GPIO.

System reset: resets all registers of the entire chip, including RTC.

In most cases, APP_CPU and PRO_CPU will be reset immediately, and some reset sources can only reset one of them.

The reset reasons for APP_CPU and PRO_CPU are also different:

After the system is reset,

PRO_CPU can get the reset source by reading the register RTC_CNTL_RESET_CAUSE_PROCPU;

APP_CPU can get the reset source by reading the register RTC_CNTL_RESET_CAUSE_APPCPU.

rst cause during ESP32 startup

For example, when the ESP32 starts, it will print the following:

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)

![image-20220610215828960](https://pic.imgdb.cn/item/62a4076b09475431293aea96.png![Image](xxx.png#center))

ESP32 power-on boot mode

When the ESP32 is powered on, it will determine the boot mode based on the status of the strapping pins.

For example, two common power-on prints:

Firmware download mode:

rst:0x1 (POWERON_RESET),boot:0x3 (DOWNLOAD_BOOT(UART0/UART1/SDIO_REI_REO_V2)) 

Chip running mode:

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)

Take ESP32-WROOM-32 as an example.

The boot value is determined by the 6-bit value of the strapping pins [MTDI, GPIO0, GPIO2, GPIO4, MTDO, GPIO5].

Article link: https://blog.csdn.net/espressif/article/details/107977962

                                                                                                            Good luck to everyone!

# Chapter 6  Appendix (PCB Wiring Diagram)

## Mainboard

![image-20220610215938488](https://pic.imgdb.cn/item/62a4077409475431293af45f.png![Image](xxx.png#center))

![image-20220610215946199](https://pic.imgdb.cn/item/62a4087c09475431293c14e5.png![Image](xxx.png#center))

![image-20220610215952810](https://pic.imgdb.cn/item/62a4077809475431293afa5a.png![Image](xxx.png#center))

![image-20220610215959236](https://pic.imgdb.cn/item/62a4077d09475431293b00c7.png![Image](xxx.png#center))

![image-20220610220005265](https://pic.imgdb.cn/item/62a4085009475431293bdf91.png![Image](xxx.png#center))

![image-20220610220011824](https://pic.imgdb.cn/item/62a4078209475431293b0634.png![Image](xxx.png#center))

![image-20220610220018753](https://pic.imgdb.cn/item/62a4082c09475431293bb7fa.png![Image](xxx.png#center))

![image-20220610220024328](https://pic.imgdb.cn/item/62a4078509475431293b0cc1.png![Image](xxx.png#center))

## Expansion Board

`#①  Version 2.0 #(yellow)`

![image-20220610220056134](https://pic.imgdb.cn/item/62a4078b09475431293b13ad.png![Image](xxx.png#center))

![image-20220610220102884](https://pic.imgdb.cn/item/62a4079109475431293b1a19.png![Image](xxx.png#center))

`#①  Version 1.5 #(yellow)`

![image-20220610220117345](https://pic.imgdb.cn/item/62a4079e09475431293b267c.png![Image](xxx.png#center))

![image-20220610220122839](https://pic.imgdb.cn/item/62a4079d09475431293b262f.png![Image](xxx.png#center))

`#①  Version 1.2 #(yellow)`

![image-20220610220134279](https://pic.imgdb.cn/item/62a407a209475431293b2b89.png![Image](xxx.png#center))

![image-20220610220140492](https://pic.imgdb.cn/item/62a407a309475431293b2cc6.png![Image](xxx.png#center))
