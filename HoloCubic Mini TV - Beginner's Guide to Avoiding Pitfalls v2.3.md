###### <sub>All In One™</sub><br />Zhihui Jun's `HoloCubic` Mini TV<br />──<br /><sup>Beginner's Guide</sup><br />`#Latest Version|V2.3#`<br /><br /><br />**Su Jian Dan Mo, Liu Ma Xiao Ge, Mysterious Treasure Room, Wu Chang Miao Tai, Zui Meng, Dong Xiao Xin, Xiao Er Hei, Wan Nan Romantic Revolution, Hui Qian, Yi Ye Zhi Qiu**<br />*Must-read for group navigation*

[TOC]

# Chapter 1  Preface

This document is from `#HoloCubic AIO Multifunctional Firmware Group 755143193 #(blue)`, and it is a detailed description of the production of `#HoloCubic #(blue)` and `#AIO Firmware (All in One) #(orange)`. Introduction to the transparent mini TV: https://www.bilibili.com/video/BV1jh411a7pV?p=6. If you have any questions, please ask more, and be polite. Group members are all volunteering their time. `#Note: Read the manual before asking questions #(orange)`

The main content of this document is compiled based on existing materials in the group.

Original author's project link: https://github.com/peng-zhihui/HoloCubic

Group owner's project address: https://github.com/ClimbSnail/HoloCubic_AIO (latest version) or: https://gitee.com/ClimbSnailQ/HoloCubic_AIO

`#Video references: #(red)`

`#Group owner (ClimbSnail Bilibili: Liu Ma Xiao Ge) | Video Collection 📝 #(blue)`:

https://www.bilibili.com/video/BV1jh411a7pV/?spm_id_from=333.788.recommend_more_video.0

`#Yi Ye Zhi Qiu's | Nanny-level Tutorial #(blue)`: https://www.bilibili.com/video/BV11h41147iJ?spm_id_from=333.999.0.0

`#Mysterious Treasure Room's | [Production Pitfalls] 💡 #(blue)`: https://b23.tv/WuBqTGO

`#Hui Qian's | Soldering Reference Tutorial #(blue)`: https://b23.tv/A83JUGt?share_medium=android&share_source=qq&bbid=BBCEC45F-7A83-45A8-B161-5384DDA3085232266infoc&ts=1651579335471

`#Group member Xue Ding_E_Le Me's | Tutorial Reference #(blue)`: https://www.bilibili.com/video/BV1eu411i7Qo?p=1&share_medium=android&share_plat=android&share_session_id=8f9d7992-dfe1-46c9-84b6-055729c97ae0&share_source=QQ&share_tag=s_i&timestamp=1654861439&unique_k=JUQMGWO

Others to be added...

# Chapter 2  Hardware, Shell, and Other Production

`#All hardware files involved in Chapter 2 are in the "Hardware Shell Related" group folder | Corresponding version compressed package #(yellow)`

## Preparation Before Hardware Production

Install Altium Designer (referred to as "AD", available in the group folder "Developer Tools", can be downloaded by yourself)

Purpose of installation: ① Convenient to open schematics & PCB for viewing when there are soldering issues

② Packaging for the board factory (e.g., JLCPCB) to avoid single order suspicion, it is recommended to add or delete some silkscreen. (If you don't know how to modify or generate Gerber files, you can use "Huaqiang DFM" to directly generate Gerber files, the method is in 2.3.2)

![image-20220610202303750](https://pic.imgdb.cn/item/62a337ac0947543129627416.png![Image](xxx.png#center))

`#Install "JLCPCB Order Assistant" - Essential for free #(orange)`

Download link (top right corner: Download PC Assistant): https://www.jlc.com/?s=AD&sdclkid=AL2s152ibJDibOfpA5gD&renqun_youhua=727919&bd_vid=11596835000121341583

![image-20220610202449490](https://pic.imgdb.cn/item/62a338150947543129630ab0.png![Image](xxx.png#center))

## Hardware Versions (Image source from group members)

Zhihui Jun has four versions in total: Transparent Base Version Naive, Metal, Ironman Version, and BiliBili Angel Base.

Most group members use the Transparent Base Naive Version.

`#①  Transparent Base Naive Version | (Board thickness recommended 1.2mm) #(cyan)`:

![image-20220610203418927](https://pic.imgdb.cn/item/62a33a4f0947543129665b5b.png![Image](xxx.png#center))

`#②  Metal Version | (Board thickness recommended 1.2mm [Transparent Metal 2.0 supports 1.6mm, recommended 1.2mm]) #(cyan)`:

<img src="https://pic.imgdb.cn/item/62a33a7009475431296687a3.png![Image](xxx.png#center)" alt="image-20220610203452685" style="zoom:67%;" />

`#③  Ironman Version | (Zhihui Jun's original file, board thickness recommended 1.0mm) #(cyan)`:

 <img src="https://pic.imgdb.cn/item/62a33af50947543129674a03.png![Image](xxx.png#center)" alt="image-20220610203558203" style="zoom:80%;" />

`#④ BiliBili Angel Version | None #(cyan)`

 <img src="https://pic.imgdb.cn/item/62a33afc09475431296753fa.png![Image](xxx.png#center)" alt="image-20220610203621211" style="zoom:80%;" />

Most group members use the Transparent Base Naive Version. The group owner also made many Metal versions. Some group members made the Ironman head version (as shown in Figure 2.2).

 ![image-20220610203652890](https://pic.imgdb.cn/item/62a33b020947543129675d06.png![Image](xxx.png#center))

                                                                                                                              Figure 2.2

Many experts have written different firmware, and the firmware of each version is basically universal (Metal, Naive) for these two hardware versions (at least the group owner's AIO firmware is fully compatible).

Choose the version you like. Some circuits of the original author Zhihui Jun have timing issues (`#Need to change the C7 capacitor to 1uF~10uF to solve #(orange)`), and there are improved versions in the group (`#Be sure to check the latest version in the group files #(orange)`).

Note:

**①** `#The hardware only supports 2.4G wifi. #(yellow)` 5G and dual-band are not supported. No firmware can break the hardware limitations.

**②** `#For non-science/engineering majors, no electronic foundation, average hands-on ability, and want to play #(yellow)`, it is recommended to ask group members. Some group members have finished products for transfer or sale (`#The cost of making it yourself is about 200 yuan, please be cautious #(yellow)`).

**③** Be sure to ask group members if you are unsure about purchasing components!!!

**④** `#For the new DC-DC (metal) version, LDO (LP2992 or ME6211C33), DCDC (MP1471) choose one of the two [if MP1471 is soldered, the LDOs on the expansion board and the main board must be removed]. #(yellow)`

**⑤** The compatibility of Metal and Naive needs to check the latest ( `#version packages in the group #(yellow)`)

## PCB Prototyping
### File Download and Instructions

`#Step 1 #(orange)`: After `#learning and understanding the group materials #(yellow)` in 2.2, confirm the hardware version, and find the corresponding PCB file in the AIO group files for download (the group files are updated regularly, and old files will be removed).

`#Note: The group files have been improved and tested by the group owner #(red)`

![image-20220610212836190](https://pic.imgdb.cn/item/62a3e6130947543129190deb.png![Image](xxx.png#center))

![image-20220610212850946](https://pic.imgdb.cn/item/62a3e6260947543129191ed2.png![Image](xxx.png#center))

                                                                                                                   `#2.3.1|File Download #(lime)` 

`#Step 2 #(orange)`: After downloading, unzip it, and five files will appear as shown in Figure 2.3.2 (the latest file has a `one-click generation of board files` program). Take the Metal version as an example.

![image-20220610213015473](https://pic.imgdb.cn/item/62a3e63f0947543129193380.png![Image](xxx.png#center))

                                                                                                                    `#2.3.2|Unzip Files #(lime)` 

![image-20220610213035457](https://pic.imgdb.cn/item/62a4025c094754312935287f.png![Image](xxx.png#center))

![image-20220610213044184](https://pic.imgdb.cn/item/62a4026e0947543129353d31.png![Image](xxx.png#center))

                                                                                                           `#2.3.3|Main Board Folder File Description #(lime)`

![image-20220610213100688](https://pic.imgdb.cn/item/62a4028b0947543129355f73.png![Image](xxx.png#center))

![image-20220610213107948](https://pic.imgdb.cn/item/62a402990947543129356d76.png![Image](xxx.png#center))

                                                                                                      `#2.3.4|Expansion Board Folder File Description #(lime)`

### PCB Modification Tutorial (This is the old method, now obsolete)

`#Note: Be sure to modify the silkscreen before placing an order #(orange)`, add or delete silkscreen, and then compress the PCB file and send it to JLCPCB. If you don't know how to generate Gerber files, you can download a "Huaqiang DFM" software.

![image-20220610213219026](https://pic.imgdb.cn/item/62a3e67c0947543129196627.png![Image](xxx.png#center))

                                                                                                             `#Figure shows AD09 adding silkscreen #(lime)`

#### How to Use Huaqiang DFM to Generate Gerber

Huaqiang DFM download link: https://dfm.elecfans.com/index

Cloud disk download link: https://www.aliyundrive.com/s/vh9fgUf57jz

`#①  Common Gerber File List #(purple)`

When making PCB boards, the Gerber files submitted to the board factory must include 1-10 and 15 below. 11-14 are optional but recommended to be included.

1. GTO (Top Overlay): Top layer silkscreen, usually white.

2. GTS (Top Solder): Top layer solder mask, usually green.

3. GTL (Top Layer): Top layer routing.

4. GTP (Top Paste Mask): Top layer paste mask.

5. GBP (Bottom Paste Mask): Bottom layer paste mask.

6. GBL (Bottom Layer): Bottom layer routing.

7. GBS (Bottom Solder): Bottom layer solder mask, usually green.

8. GBO (Bottom Overlay): Bottom layer silkscreen, usually white.

9. GMX (Mechanical) or GKO (Keep-out Layer): Used to define the board outline, select the layer where the outline is located.

10. GX (Mid Layer): Middle signal X layer, one file for each middle layer.

11. GD (Drill Drawing): Drill drawing layer.

12. GG (Drill Guide): Drill guide layer.

13. GPT (Top Pad Master): Top layer pad.

14. GPB (Bottom Pad Master): Bottom layer pad.

15. NC drill Files: Drill files, usually txt files when exported from AD. Typically includes: ① RoundHoles-NonPlated (Non-plated round holes) ② RoundHoles-Plated (Plated round holes) ③ SlotHoles-Plated (Plated slot holes).

`#②  Explanation of Gerber Files #(purple)`

1. Top Overlay/Bottom Overlay: Top and bottom silkscreen layers, showing component outlines, reference designators, attributes, and annotations.

2. Top Solder/Bottom Solder: Top and bottom solder mask layers, showing areas not covered by solder mask, such as pads and openings.

3. Top Layer/Bottom Layer: Top and bottom routing layers, showing routing information.

4. Mechanical or Keep-out Layer: Used for mechanical drawings, such as PCB outlines. Shapes on this layer appear on all layers and are not covered by solder mask. Typically used for board outlines.

5. Top Paste Mask/Bottom Paste Mask: Used for stencil files.

6. Drill Drawing, Drill Guide, and NC drill Files contain drilling information. Drill Drawing and Drill Guide are used for manual drilling, while NC drill Files are for CNC drilling.

`#Step 1 #(yellow)`: Open Huaqiang DFM, register/login if prompted, then click File → Open → PCB (the PCB file to generate Gerber).

![image-20220610213545135](https://pic.imgdb.cn/item/62a4048a0947543129379f71.png![Image](xxx.png#center))

                                                                                                                            `# Import PCB #(lime)`

![image-20220610213611294](https://pic.imgdb.cn/item/62a404a1094754312937b627.png![Image](xxx.png#center))

                                                                                                                       `# Importing #(lime)`                   

`#Step 2 #(yellow)`: After opening, you will see the Gerber files as shown below.

![image-20220610213634982](https://pic.imgdb.cn/item/62a404b7094754312937ce42.png![Image](xxx.png#center))

![image-20220610213642912](https://pic.imgdb.cn/item/62a404ca094754312937e2ac.png![Image](xxx.png#center))

`#Step 3 #(yellow)`: Select the file, export the Gerber file, choose the folder to export to, and you will be prompted when the export is successful.

![image-20220610213700360](https://pic.imgdb.cn/item/62a404d7094754312937f1d6.png![Image](xxx.png#center))

![image-20220610213709034](https://pic.imgdb.cn/item/62a404fd0947543129381f79.png![Image](xxx.png#center))

![image-20220610213716614](https://pic.imgdb.cn/item/62a405290947543129384e4f.png![Image](xxx.png#center))

`#Step 4 #(yellow)`: Check the exported Gerber files in the folder, confirm, and compress them into a package.

![image-20220610213732789](https://pic.imgdb.cn/item/62a4051109475431293834bc.png![Image](xxx.png#center))

`#Step 5 #(yellow)`: Compare the exported Gerber files with the list above to ensure none are missing or extra.

![image-20220610213749660](https://pic.imgdb.cn/item/62a40564094754312938a2af.png![Image](xxx.png#center))

### JLCPCB Prototyping (Refer to the Naive version Holo3 production tutorial by the group admin)

`#Step 1 #(yellow)`: Use the `one-click generation of JLCPCB free Gerber files` in the corresponding version's PCB folder, double-click to generate the latest board files. Compress each gerber subfolder in the generated `AIO_Gerber_xxx` folder into a package.

`#Step 2 #(yellow)`: Open the JLCPCB order software, upload the compressed board files, and wait patiently for the parsing process.

![image-20220610213839623](https://pic.imgdb.cn/item/62a405ef0947543129393716.png![Image](xxx.png#center))

                                                                                                                        `# Upload PCB Files #(lime)`

![image-20220610213854642](https://pic.imgdb.cn/item/62a406250947543129397cdb.png![Image](xxx.png#center))

                                                                                                                            `# PCB File Parsing #(lime)`  

`#Step 3 #(yellow)`: After parsing, the order options will appear as shown below. The board's length and width are usually automatically recognized. If not, you can fill in any value, such as 5x5, and the board factory will adjust it. The board quantity is 5 (more than that cannot be free).

![image-20220610213917796](https://pic.imgdb.cn/item/62a4062e0947543129398733.png![Image](xxx.png#center))

`#Step 4 #(yellow)`: Choose the board thickness according to the version of the mini TV.

![image-20220610213934524](https://pic.imgdb.cn/item/62a406350947543129398fca.png![Image](xxx.png#center))

                                                                                                                        `# Board Thickness Selection #(lime)`

`#Step 5 #(yellow)`: Choose the solder mask color according to your preference.

![image-20220610213949548](https://pic.imgdb.cn/item/62a4063c094754312939981a.png![Image](xxx.png#center))

                                                                                                                     `# Solder Mask Color Selection #(lime)`   

`#Step 6 #(yellow)`: Whether to open the stencil file.

Note: It is recommended for beginners to open the main board's front stencil. The group will provide the stencil file, and you can find a seller on Taobao to make the stencil, costing around 10-20 yuan (excluding shipping).

![image-20220610214027440](https://pic.imgdb.cn/item/62a406430947543129399ed7.png![Image](xxx.png#center))

                                                                                                                    `# Stencil File #(lime)`    

## Material and Tool Purchase

### Component Purchase (Refer to the BOM table in the AIO group online document)

**①** The file contains a BOM, and you can purchase components based on the BOM (recommended to buy from Taobao Yuxin Electronics). MPU 6050 can be purchased as a module and disassembled. You can also refer to the recommended links in the group online document: https://docs.qq.com/sheet/DQUpSbmN4TVNha0h0

**②** The screen can be purchased from Taobao Zhongjingyuan (brand Hancai [currently the best display effect]).

**③** If you are unsure or uncertain, you can ask group members.

**④** The voltage rating of capacitors/resistors should be ≥5V (e.g., 16V, 24V, 50V, etc.) [only for this project].

**⑤** The connector socket model is: flip-top down 8P (used for both the expansion board and the main board), and the cable should be the same direction 0.5 * 8P (Naive recommended 6cm, Metal uses 3cm).

**⑥** Zhihui Jun's original card slot model is DM3D-SF (not recommended). The improved card slot can be found in the group online document link or search for flip-top internal welding TF card slot (8P) on Taobao.

**⑦** When purchasing LDO, be sure to pay attention to the model. ME6211C33 [the 33 at the end indicates 3.3V]. Some group members bought the wrong one.

Note: It is recommended to buy 1-2 extra for certain components. It is recommended to buy 6-8 flip-top down 8P sockets.

<img src="https://pic.imgdb.cn/item/62a4064a094754312939a75c.png![Image](xxx.png#center)" alt="image-20220610214236590" style="zoom:67%;" />

**⑦** Memory card selection

The firmware has certain compatibility issues with memory cards, and not all are compatible. Currently, it supports `#SD, SDHC types of memory cards, and does not support SDXC! #(orange)` The following verified memory cards are recommended.

① Aigo 32G ordinary card. About 20 yuan on Taobao (high cost performance, recommended).

② Sandisk 32G ordinary card. About 30 yuan on Taobao.

⑧ Screen issues

Screen specifications: 1.3 inches, driver ST7789, resolution 240*240, soldered 12Pin. Most screen boards have a metal shell, `#pay attention to short circuit issues! #(orange)`

There are many such screens online, but for making Holocubic, you need to choose carefully. The screen will affect the overall display effect. After testing many screens, the best effect is from Zhongjingyuan.

Other screens are not recommended for making Holocubic. Below is an actual comparison (please ignore the background difference):

Left: Zhongjingyuan (Hancai)  Right: Youzhijing

![image-20220611203259749](https://pic.imgdb.cn/item/62a48b7f0947543129e84767.png![Image](xxx.png#center))  

The difference between the two screens after applying the prism is mainly that the blank area around the Youzhijing screen is severely blue, which greatly affects the final effect. The blank area of the Zhongjingyuan screen is very clean. Note: In fact, the base color of Zhongjingyuan is also slightly blue, but very slightly.

Regarding brightness issues (unrelated to the screen):

The above image also shows that the left side is significantly brighter because the left side has not removed the protective film of the factory polarizer (which can increase brightness), and the color of the left side becomes extremely inaccurate due to the refraction of the protective film.

Those who have done experiments will also find that after removing the protective film, the brightness of the prism placed on the X-axis and Y-axis is different. The human eye is more sensitive to color than brightness. It is recommended to remove the protective film (`#Brightness can be improved by purchasing a 6:4 prism, which is slightly brighter than a 5:5 prism #(orange)`).

Of course, if you care more about brightness, you can keep the protective film. When buying the screen, you can ask the seller to send it with the protective film and not to attach the green label to the protective film.

### Production Tools (Refer to the group owner)

`#①|Soldering Tools #(orange)` 

Soldering iron (936 soldering station, cost-effective, various soldering iron tips);

Soldering station, also known as: Teppanyaki (500w Deer Fairy);

Tweezers (0402 size is small, recommended to use pointed tweezers);

Solder wire (0.3mm/0.5mm/1.0mm DIY commonly used specifications);

Flux and solder paste are recommended to buy from repairers (if conditions permit, you can buy Japanese brands from Amazon).

`#②|Sandpaper #(orange)`

300 grit, 800 grit, 5000 grit, 8000 grit, buy according to demand (the larger the number, the finer the grinding).

High-transparency shells are frosted shells, polished with fine sandpaper and sprayed with varnish.

`#The group owner recommends 400 and 800 grit, coarse grinding + fine grinding. 800 grit can produce a frosted effect. Additionally, grinding requires running water to avoid scratches. #(yellow)`

`#③|Glue (refer to the group owner's tutorial) #(orange)`

704 glue (used to seal the gaps around the screen), UV glue or B-7000 [used to bond the screen]. Note: UV glue requires an additional curing lamp. Prism bonding video tutorial: https://www.bilibili.com/video/BV1jh411a7pV?p=5

### Shell Production

Pure white can be ordered from Sanwei Monkey (JLCPCB).

Semi-transparent can be ordered from Future Factory or Taobao (you can also consult group members).

Metal CNC (the car has already left) [you can wait for the group owner's Ironman car].

## 3D Printing of the Shell

`#All the latest model files are in the corresponding version package in the group!!! #(yellow)`

`#①|Naive Transparent Base (Improved Version) #(orange)`  

1. Suitable for Naive version hardware.

2. The original design plan uses screws to connect the upper and lower shells, but there is an improved version with magnetic attraction (the magnet is a 3*3mm round magnet) recommended to use the improved version.

3. The base is made with a 3D printer, and it is recommended to use a semi-transparent printing effect.

4. If you want to make the printed surface frosted, it is recommended to use 800 grit sandpaper to polish it under running water.

5. If you are looking for online printing services, pay attention to tolerances. If the shell is too small, the main board will not fit.

6. Main board thickness 1.2mm (using the improved shell). Expansion board thickness 1.2mm.

`#②|Metal Base (Improved Version) #(orange)`

1. Suitable for Metal version hardware.

2. The base is made with a 3D printer, and it is recommended to use a semi-transparent printing effect.

3. If you want to make the printed surface frosted, it is recommended to use 800 grit sandpaper to polish it under running water.

4. Both v1.0 and v2.0 versions are modified based on Zhihui Jun's original version, with an internal memory card slot at the bottom.

5. Both v1.0 and v2.0 are compatible with all versions of the main board and expansion board in this folder. It is recommended to use 1.2mm thick PCB boards (main board and screen board).

`#V 1.0's left and right reinforcement seats are too large, V2.0 optimizes this defect. #(yellow)`

`#③|Ironman Base #(orange)`

1. Suitable for Ironman version hardware.

2. Zhihui Jun's original base recommends: main board thickness 1.0mm. Expansion board thickness 1.0mm.

`#④|BiliBili #(orange)`

No base yet. (See group files)

`#⑤|Ironman Head #(orange)`

No base yet. Open source address: https://gitee.com/qlexcel/holo-iron-man

## Using and Creating Dynamic BOM
Purpose: Dynamic placement files can improve the efficiency of soldering components on the PCB. It is recommended to use. The AIO materials already include this tool and can be used directly.
### Using Dynamic BOM

`#Step 1 #(yellow)`: Open the soldering diagram file marked in 2.2.2

![image-20220610214348237](https://pic.imgdb.cn/item/62a40655094754312939b2d0.png![Image](xxx.png#center))

`# Open the soldering silkscreen diagram file #(lime)`

`#Step 2 #(yellow)`: Click on the component on the left with the mouse, and it will display specific content (similar components will also be highlighted).

![image-20220610214411109](https://pic.imgdb.cn/item/62a4065a094754312939b798.png![Image](xxx.png#center))

`#Step 3 #(yellow)`: If you want to see the first pin of the component, you can set it in the upper right corner settings.

![image-20220610214431618](https://pic.imgdb.cn/item/62a40661094754312939be18.png![Image](xxx.png#center))

### Creating Dynamic BOM (This is for extended learning, not a necessary operation)

![image-20220610214454029](https://pic.imgdb.cn/item/62a4066a094754312939c9ae.png![Image](xxx.png#center))

![image-20220610214510405](https://pic.imgdb.cn/item/62a40670094754312939cf4a.png![Image](xxx.png#center))

Note: AD script link for creating dynamic BOM: https://github.com/lianlian33/InteractiveHtmlBomForAD

If you can't open it, you can download it from the cloud disk: https://www.aliyundrive.com/s/f6VVYfwsQ3S

Or in the group file "Developer Tools" inside "InteractiveHtmlBomForAD"

## Improved Expansion Board Introduction

`#V 1.5 #(orange)`

1. Improved version of the expansion board, added 662k 3.3v 300ma voltage regulator chip (shared the screen current, thereby reducing the device restart caused by insufficient power supply of the main board 2992 voltage regulator chip);

2. The expansion board is also suitable for MetalV2.0 shell.

![image-20220610214555211](https://pic.imgdb.cn/item/62a40677094754312939d797.png![Image](xxx.png#center))

![image-20220610214602286](https://pic.imgdb.cn/item/62a4067c094754312939dd3a.png![Image](xxx.png#center))

`#V 2.0 #(orange)`

1. Improved version of the expansion board, added MP1471 power management chip (reduces the device restart and heating problems caused by insufficient power supply of the main board LP2992 or ME6211 voltage regulator chip);

2. The expansion board is suitable for MetalV2.0 shell, Naïve needs to modify the mold.

![image-20220610214704307](https://pic.imgdb.cn/item/62a40681094754312939e153.png![Image](xxx.png#center))

## PCB to PCBA Soldering

Note: Refer to the group file "Some Troubleshooting Methods for Main Control Board Soldering Issues"

Due to the 0402 package of the main control board components, it is somewhat difficult for non-science/engineering majors, no electronic foundation, average hands-on ability, and no soldering experience. As for the difficulty, it depends on your "skills".

Generally, it is soldered in the order of the size of the components, from small to large. It is recommended to use a desoldering station or a hot air gun, and it is not recommended to use only a soldering iron. For those who have never soldered anything, or only done electronic and electrical internships, it is recommended to buy a heating station. There is a 20-yuan Deer Fairy desoldering station on Taobao (please refer to Bilibili for the usage method of the soldering station), which is completely sufficient (of course, the rich can buy a combination of a hot air gun and a soldering station), and then a soldering iron can be used.

All components on the back of the main control board (SD card slot and 4 resistors) will not affect the normal use of the board if not soldered. It is recommended to solder the screen, test it, and then solder it.

Regarding the difficulty of tinning: It is recommended to use a stencil for those who don't understand anything. For those who have never done it, it is recommended to use the stencil in the group file. After applying the solder paste with the stencil (the solder paste can be medium temperature solder paste, a small can of 30 grams can be used for a long time, 20 yuan on Pinduoduo), place the components according to the welding reference diagram in the group, and then heat it on the heating station. During the soldering process, the position of the components will be offset, and you can adjust the position with tweezers. (Note: When soldering the esp32, place the chip in position, and after the solder melts, turn off the heating station switch, and press the chip with tweezers while cooling)

PS: C7 capacitor can be selected from 1uF to 10uF. (Especially for those bought on Taobao "Geek***", pay attention)

### Main Control Board PCB Soldering Start

`#①|Ensure that the computer port can recognize [Be sure to use a multimeter to measure whether the power and ground are short-circuited before powering on] #(yellow)`

`#Step 1 #(yellow)`: Solder the LDO and surrounding resistors and capacitors

Resistors, capacitors, transistors (VT1-2, 8050), voltage regulator chip (LP2992) are soldered first, the antenna (A1) and light (D1) can be soldered last.

![image-20220610214819180](https://pic.imgdb.cn/item/62a4068c094754312939ecac.png![Image](xxx.png#center))

`#Step 2 #(yellow)`: Solder CP2102 and Type C interface,

After the first step of soldering, prepare to solder CP2102 (U1) and Type C interface. If there is no problem with this part of the soldering, the board can be recognized by the computer's device manager when plugged into the computer (use a multimeter to measure whether VCC (5V) and GND are short-circuited before plugging into the computer).

![image-20220610214835779](https://pic.imgdb.cn/item/62a40691094754312939f2c7.png![Image](xxx.png#center))

Note: Soldering direction - chip dot to PCB white

![image-20220610214852463](https://pic.imgdb.cn/item/62a40696094754312939f847.png![Image](xxx.png#center))

`#②|Common soldering problems in this part #(yellow)`:

`#Ⅰ|No response after plugging into the computer #(cyan)`

Most likely it is a virtual soldering. First, check with the naked eye or a magnifying glass to see if there is any solder bridge, then check the voltage of the LP2992 (ME6211) pins with a multimeter in the case of connecting to the computer or power supply to see if there is 5V and 3.3V output, then check if CP2102 and Type C, and R1 resistor are soldered properly, press with tweezers.

`#Note: Do not use a data cable that can only charge, it must be able to transmit data #(yellow)`

`#Ⅱ|The computer prompts USB port abnormal current after plugging in #(cyan)`

![image-20220610214915062](https://pic.imgdb.cn/item/62a4069c094754312939fda8.png![Image](xxx.png#center))

The board's VCC and GND are short-circuited or the LDO is broken. (To avoid unexpected losses, it is recommended to measure whether the power [5V & 3V3] and ground [GND] are short-circuited before powering on)

`#Solution #(orange)`: Check the board, re-solder or replace an LDO

`#Ⅲ|The computer recognizes CP2102, but there is a yellow exclamation mark #(cyan)`

`#Solution #(orange)`: The driver is not installed, the group file has the driver, download and install the driver.

`#Ⅳ|Others #(cyan)`

It may still be a virtual soldering or the direction is wrong or the chip is broken, check the voltage of the 2992 pins to see if there is 5V and 3.3V output, then check CP2102 and Type C.

`#Solution #(orange)`: Check if it is a virtual soldering or if it is a problem with the Type-C socket.

`#Ⅴ| CP2102 driver is modified #(cyan)`

`#Solution #(orange)`:

![image-20220610215014567](https://pic.imgdb.cn/item/62a406a109475431293a047d.png![Image](xxx.png#center))

![image-20220610215021227](https://pic.imgdb.cn/item/62a406a709475431293a0ab6.png![Image](xxx.png#center))

![image-20220610215027585](https://pic.imgdb.cn/item/62a406b609475431293a20f6.png![Image](xxx.png#center))

`#③|Ensure that ESP32 can communicate with the serial port normally #(yellow)`

`#Step 3 #(yellow)`: Solder the esp32 (U4) chip

![image-20220610215040004](https://pic.imgdb.cn/item/62a406be09475431293a2950.png![Image](xxx.png#center))

Note: ESP32 soldering direction - chip dot to PCB diagonal

After the serial port is no problem, start soldering the ESP32. This should be the most difficult chip to solder on the board. Sometimes after soldering, the ESP32 chip can work normally, the program can be burned, and the blink light can flash normally, but it does not mean that your soldering is fine. There may still be partial IO pin short circuits or virtual soldering, causing the screen not to light up or display problems, or even MPU6050 cannot connect normally, etc.

Note:

**①** The TF card slot and four 10K pull-up resistors on the back do not affect burning and use.

**②** Please synchronize the firmware burning with the latest firmware in the group file, try not to use the "ancient" firmware.

**③** If the firmware is successfully burned, the LED may not light up (it may be virtual soldering or the light is broken), but if the firmware is not successfully burned, the LED will definitely not light up.

Your computer burns the program through USB →Type C→CP2102→ESP32. Any communication failure in the middle will cause the firmware burning to fail.

After soldering, you can first use the upper computer to check if there is serial information printed. `#Check the baud rate of the serial print is 115200 #(yellow)` (Baud rate: 115200 [not 1152000, nor 921600 (use 921600 when downloading, of course, 115200 can also be used, just slower)]), if the soldering is fine (only indicates that the serial port can communicate with ESP32 normally, does not mean that other IO ports are fine), there will be serial information, and there will be no virtual soldering.

`#Under normal soldering conditions, the voltage of the two 8050 collector electrodes, that is, the top Pin foot, is about 3.3V. #(yellow)`

![image-20220610215100448](https://pic.imgdb.cn/item/62a406c309475431293a2ef1.png![Image](xxx.png#center))

Regarding the above rst: and boot related instructions, see Chapter 5, ESP32 Basics.

`#④|Common soldering problems in this part #(yellow)`

`#Ⅰ|Burning fails after plugging into the computer #(cyan)`

The upper computer is stuck at the last point & using VS Code to burn prompts connect ESP 32 time out ...---...----...---- This situation is mostly because the ESP32 is virtual soldered. Any connection failure, or flash error, is because the ESP32 chip is virtual soldered. Re-solder, too much tin (causing pin adhesion) or too little tin (not soldered) will cause this problem. Use tweezers, flux, solder wick, and desoldering station flexibly.

`#Solution #(orange)`: Add tin and re-solder, you can refer to the video on the homepage. (If it is useful or successful, remember to give them a thumbs up 😁)

![image-20220610215119591](https://pic.imgdb.cn/item/62a406d309475431293a3e6c.png![Image](xxx.png#center))

`#Ⅱ|C7 capacitor is 0.1uF #(cyan)`

Zhihui Jun's original file uses 0.1uf, so those who use Zhihui Jun's source file to make the board, the C7 capacitor is basically 0.1uF. If C7 is soldered with a 0.1uF capacitor, and the program download fails, but during the program download process, the program can be downloaded normally after shorting the GPIO0 pin of the ESP32, it is recommended to change the C7 capacitor to 1uF~10uF.

`#Solution #(orange)`: Change the C7 capacitor to 1uF~10uF.

![image-20220610215133241](https://pic.imgdb.cn/item/62a406da09475431293a4694.png![Image](xxx.png#center))

`#Ⅲ|Others #(cyan)`

It may also be that the CP2102 chip and R3 resistor are not soldered properly, or the two transistors, or the four small components next to U2...

`#Solution #(orange)`: Re-solder and try again.

`#Ⅳ |Always restart after burning #(cyan)`

It may be that other pins of the 32 are virtual soldered or soldered together, causing continuous restart. Being able to burn and read the serial port only means that the burning pin is fine, it does not mean that other pins of the 32 are fine.

![image-20220610215159437](https://pic.imgdb.cn/item/62a406ec09475431293a5b22.png![Image](xxx.png#center))

`#Solution #(orange)`: Add solder, move with tweezers, and gently press to squeeze out the excess tin inside.

![image-20220610215149636](https://pic.imgdb.cn/item/62a406e109475431293a4e1e.png![Image](xxx.png#center))

`#⑤|Un-soldered parts on the front of the main control board #(yellow)`

`#Step 4 #(yellow)`: Solder the remaining components on the front

If your ESP32 can burn the program normally, then you are only 50% away from success.

MPU6050, FPC 8P socket, RGB light, 2.4G antenna, light sensor (can be unsoldered)

![image-20220610215216982](https://pic.imgdb.cn/item/62a406f809475431293a6a01.png![Image](xxx.png#center))

Note: MPU 6050 soldering direction - dot to white dot; 2.4G antenna dot to horizontal bar; light sensor AA to white dot.

`#⑥|Common problems in this part #(yellow)`:

`#Ⅰ |APP switches by itself #(cyan)`

(1) The initialization is not completed after power-on

`#Solution #(orange)`: Power off and place horizontally to wait for MPU 6050 initialization to complete (the light starts to change)

(2) Virtual soldering

If your MPU6050 is virtual soldered, you will always be stuck at the initialization of MPU6050 when burning the test firmware in the group, making you start to doubt life, whether your ESP32 chip is broken again.

`#Solution #(orange)`: Re-solder. (You can refer to the video of the mysterious treasure brother)

(3) Bypass capacitor of MPU 6050

Some group members have the phenomenon of wrong or virtual soldering of the capacitors near the MPU 6050.

`#Solution #(orange)`: Add solder to MPU 6050 (if adding solder does not work, you can try adding solder to the two pins in the lower right corner of ESP 32) and the nearby capacitors (or directly replace and re-solder).

![image-20220610215235637](https://pic.imgdb.cn/item/62a4070109475431293a73d1.png![Image](xxx.png#center))

`#Ⅱ |Bought fake MPU6050 & broken #(cyan)`

Through the serial information, you can see that MPU 6050 always reports ****** 80% may be broken or 20% may be virtual soldered.

![image-20220610215257158](https://pic.imgdb.cn/item/62a4070a09475431293a7ea3.png![Image](xxx.png#center))

`#Solution #(orange)`: Replace with a new MPU 6050 or add solder (80% probability is that the chip is broken, 20% probability is virtual soldering).

`#Ⅲ |Light sensor soldering problem #(cyan)`

Through the serial information, you can see that MPU 6050 reports

[E][esp32-hal-i2c.c:1434]i2cCheckLineState(): Bus Invalid State, TwoWire() Can't init sda=1, scl=0

`#Solution #(orange)`: Confirm whether the light sensor is soldered correctly or remove the light sensor and re-solder the MPU 6050. (PS: Some group members have this problem because the light sensor soldering direction is wrong)

The following picture is for reference after soldering

![image-20220610215315275](https://pic.imgdb.cn/item/62a4070e09475431293a83d9.png![Image](xxx.png#center))

### Expansion Board PCB Soldering Start

The expansion board is not difficult. Just solder the screen, FFC, and MOS tube according to the material list and PCB. Note that there are two versions of the expansion board, one is the original version (not recommended), and the other is the optimized version (it is recommended to use the latest DC-DC expansion board [full blood version] of the group owner, ME 6211 + optimized version with 622K [residual blood version]).

When soldering the screen cable, it is best not to use a desoldering station, just use a soldering iron and apply a little solder paste, otherwise, it is easy to burn the screen.

![image-20220610215342877](https://pic.imgdb.cn/item/62a40681094754312939e153.png![Image](xxx.png#center))

MP1471 soldering direction is horizontal line down

Common problems in this part

The screen board only has backlight

Please measure according to the reference voltage in the group file and troubleshoot step by step.

![image-20220610215401098](https://pic.imgdb.cn/item/62a4071d09475431293a921c.png![Image](xxx.png#center))

![image-20220610215408851](https://pic.imgdb.cn/item/62a4072409475431293a9a2f.png![Image](xxx.png#center))

Be careful when soldering the socket!!!

![image-20220610214236590](https://pic.imgdb.cn/item/62a4064a094754312939a75c.png![Image](xxx.png#center))

# Chapter 3  Upper Computer Related Issues

## Upper Computer Display Incomplete

Problem: When opening the upper computer on Windows 11 or Windows 10, the following situation may occur

Solution: Adjust the scaling ratio in the computer resolution interface. Then reopen the upper computer. If there is no change, restart the computer and try opening the upper computer again.

![image-20220610215502037](https://pic.imgdb.cn/item/62a4073009475431293aa7cf.png![Image](xxx.png#center))

## Upper Computer Serial Information

### MPU 6050 Initialization Failed

Problem: MPU 6050 initialization failed or no connection

Solution: MPU 6050 is virtual soldered, add solder to the position as shown in the main board soldering above.

![image-20220610215530444](https://pic.imgdb.cn/item/62a4073709475431293ab037.png![Image](xxx.png#center))

### TF Card Cannot Be Read (TF Card Slot Voltage Diagram)

Problem: TF card cannot be read normally or cannot be recognized after a period of time.

![image-20220610215549378](https://pic.imgdb.cn/item/62a4073b09475431293ab507.png![Image](xxx.png#center))

![image-20220610215556324](https://pic.imgdb.cn/item/62a4074109475431293abb3e.png![Image](xxx.png#center))

Solution: First confirm whether it is a problem with the memory card (TF card, note: TF card supports up to 32G). If not, it may be a virtual soldering problem. As shown in the figure below, it may be a resistor or one or more pins of the ESP32 that are virtual soldered and need to be re-soldered!

![image-20220610215610255](https://pic.imgdb.cn/item/62a4074609475431293ac050.png![Image](xxx.png#center))

### Cannot Burn

Problem: Cannot erase, progress bar stuck at the last point, no serial information (Baud rate: 115200 [not 1152000, nor 921600 (use 921600 when downloading, of course, 115200 can also be used, just slower)])

Solution: ESP 32 is virtual soldered and needs to be re-soldered. (Zhihui Jun's original version, please change the C7 capacitor to 1-10uF) Please refer to the main board soldering above.

![image-20220610215629658](https://pic.imgdb.cn/item/62a406d309475431293a3e6c.png![Image](xxx.png#center))

# Chapter 4  How to Use a Multimeter

<img src="https://pic.imgdb.cn/item/62a4075609475431293ad29a.png![Image](xxx.png#center)" alt="image-20220610215653753" style="zoom:80%;" />

Taking Fluke as an example, as shown in the figure above, the outer ring of the multimeter is generally divided into six parts: AC current gear (A~), DC current gear (A-), AC voltage gear (V~), DC voltage gear (V-), resistance gear (Ω), buzzer gear (🔈 symbol I can't type, see the picture yourself).

## Measure Voltage (Take the small TV main board as an example) [It must be DC voltage gear]

① Turn the multimeter to the DC gear (choose the appropriate gear for those with gears, generally from large to small)

② One test lead of the digital multimeter is grounded, and the other is connected to the pin or pad to be tested (as shown in the figure, one test lead is placed on the Type-C, and the other test lead is placed on the 5V pin of the LDO).

Note: Pay attention to the positive and negative poles of the pointer multimeter to avoid damage to the multimeter.

![image-20220610215717268](https://pic.imgdb.cn/item/62a4075b09475431293ad994.png![Image](xxx.png#center))

## Measure Continuity (Take the small TV main board as an example) [It must be powered off]

① Turn the multimeter to the buzzer gear (test short circuit or continuity)

② If the power (VCC) and ground (GND) of the small TV are short-circuited (one test lead is placed on GND, and the other test lead is placed on 5V or 3V3), if there is a buzzer sound, it means short-circuited (continuity), otherwise, it is not. If you check whether the component is broken (such as resistors, capacitors, etc.), place the two test leads on both ends of the component respectively. If there is a buzzer sound, it means it is broken (except for 0Ω), otherwise, it is not.

![image-20220610215736025](https://pic.imgdb.cn/item/62a4076109475431293adfee.png![Image](xxx.png#center))

# Chapter 5  ESP32 Basics: rst cause and boot mode at startup

When the ESP32 starts, the ROM CODE will read the GPIO status and rst cause status, and then determine the working mode of the ESP32.

Understanding and mastering rst cause and boot mode helps to locate certain system problems.

For example:

When the ESP32 starts, the following print will appear:

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)

The baud rate of ROM CODE is 115200

System reset introduction and rst cause when ESP32 starts

System reset introduction

The system provides three levels of reset methods, namely CPU reset, core reset, and system reset.

All resets will not affect the data in MEM. The figure shows the structure of the entire subsystem and each reset method:

![image-20220610215813843](https://pic.imgdb.cn/item/62a4076609475431293ae56c.png![Image](xxx.png#center))

CPU reset: Only resets all registers of the CPU.

Core reset: Except for RTC, it will reset all digital registers, including CPU, all peripherals, and digital GPIO.

System reset: Will reset all registers of the entire chip, including RTC.

In most cases, APP_CPU and PRO_CPU will be reset immediately, and some reset sources can only reset one of them.

The reset reasons for APP_CPU and PRO_CPU are also different:

After the system is reset,

PRO_CPU can obtain the reset source by reading the register RTC_CNTL_RESET_CAUSE_PROCPU;

APP_CPU can obtain the reset source by reading the register RTC_CNTL_RESET_CAUSE_APPCPU.

rst cause when ESP32 starts

For example, when the ESP32 starts, the following print will appear:

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)

![image-20220610215828960](https://pic.imgdb.cn/item/62a4076b09475431293aea96.png![Image](xxx.png#center))

ESP32 power-on boot mode

When the ESP32 is powered on, it will judge the status of the strapping pins and determine the boot mode.

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

## Main Board

![image-20220610215938488](https://pic.imgdb.cn/item/62a4077409475431293af45f.png![Image](xxx.png#center))

![image-20220610215946199](https://pic.imgdb.cn/item/62a4087c09475431293c14e5.png![Image](xxx.png#center))

![image-20220610215952810](https://pic.imgdb.cn/item/62a4077809475431293afa5a.png![Image](xxx.png#center))

![image-20220610215959236](https://pic.imgdb.cn/item/62a4077d09475431293b00c7.png![Image](xxx.png#center))

![image-20220610220005265](https://pic.imgdb.cn/item/62a4085009475431293bdf91.png![Image](xxx.png#center))

![image-20220610220011824](https://pic.imgdb.cn/item/62a4078209475431293b0634.png![Image](xxx.png#center))

![image-20220610220018753](https://pic.imgdb.cn/item/62a4082c09475431293bb7fa.png![Image](xxx.png#center))

![image-20220610220024328](https://pic.imgdb.cn/item/62a4078509475431293b0cc1.png![Image](xxx.png#center))

## Expansion Board

`#①  2.0 version #(yellow)`

![image-20220610220056134](https://pic.imgdb.cn/item/62a4078b09475431293b13ad.png![Image](xxx.png#center))

![image-20220610220102884](https://pic.imgdb.cn/item/62a4079109475431293b1a19.png![Image](xxx.png#center))

`#①  1.5 version #(yellow)`

![image-20220610220117345](https://pic.imgdb.cn/item/62a4079e09475431293b267c.png![Image](xxx.png#center))

![image-20220610220122839](https://pic.imgdb.cn/item/62a4079d09475431293b262f.png![Image](xxx.png#center))

`#①  1.2 version #(yellow)`

![image-20220610220134279](https://pic.imgdb.cn/item/62a407a209475431293b2b89.png![Image](xxx.png#center))

![image-20220610220140492](https://pic.imgdb.cn/item/62a407a309475431293b2cc6.png![Image](xxx.png#center))
