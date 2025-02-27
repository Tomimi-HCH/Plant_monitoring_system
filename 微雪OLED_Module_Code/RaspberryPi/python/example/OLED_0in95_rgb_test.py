#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
import os
picdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'pic')
libdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'lib')
if os.path.exists(libdir):
    sys.path.append(libdir)

import logging    
import time
import traceback
from waveshare_OLED import OLED_0in95_rgb
from PIL import Image,ImageDraw,ImageFont
logging.basicConfig(level=logging.DEBUG)

try:
    disp = OLED_0in95_rgb.OLED_0in95_rgb()

    logging.info("\r 0.95inch rgb OLED ")
    # Initialize library.
    disp.Init()
    # Clear display.
    logging.info("clear display")
    disp.clear()

    # Create blank image for drawing.
    image1 = Image.new('RGB', (disp.width, disp.height), 0)
    draw = ImageDraw.Draw(image1)
    font = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 12)
    font1 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 18)
    font2 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 24)
    logging.info ("***draw line")
    draw.line([(0,0),(95,0)], fill = "RED")
    draw.line([(0,0),(0,63)], fill = "RED")
    draw.line([(0,63),(95,63)], fill = "RED")
    draw.line([(95,0),(95,63)], fill = "RED")
    logging.info ("***draw text")
    draw.text((0,0), 'Waveshare ', font = font1, fill = "BLUE")
    draw.text((0,24), u'微雪电子 ', font = font2, fill = "MAGENTA")
    image1 = image1.rotate(0)
    disp.ShowImage(disp.getbuffer(image1))
    time.sleep(3)

    logging.info ("***draw rectangle")
    image1 = Image.new("RGB", (disp.width, disp.height), "BLACK")
    draw = ImageDraw.Draw(image1)
    draw.line([(0,4), (96,4)],  fill = "RED",    width = 8)
    draw.line([(0,12),(96,12)], fill = "YELLOW", width = 8)
    draw.line([(0,20),(96,20)], fill = "GREEN",  width = 8)
    draw.line([(0,28),(96,28)], fill = "CYAN",   width = 8)
    draw.line([(0,36),(96,36)], fill = "BLUE",   width = 8)
    draw.line([(0,44),(96,44)], fill = "MAGENTA",width = 8)
    draw.line([(0,52),(96,52)], fill = "BLACK",  width = 8)
    draw.line([(0,60),(96,60)], fill = "WHITE",  width = 8)
    disp.ShowImage(disp.getbuffer(image1))
    time.sleep(3)

    logging.info ("***draw image")
    Himage2 = Image.new('RGB', (disp.width, disp.height), 0)  # 0: clear the frame
    bmp = Image.open(os.path.join(picdir, '0in95_rgb.bmp'))
    Himage2.paste(bmp, (0,0))
    Himage2=Himage2.rotate(0) 	
    disp.ShowImage(disp.getbuffer(Himage2)) 
    time.sleep(3)    

    disp.clear()

except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    disp.module_exit()
    exit()