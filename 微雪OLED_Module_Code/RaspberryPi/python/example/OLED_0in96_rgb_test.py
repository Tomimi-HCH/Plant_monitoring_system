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
from waveshare_OLED import OLED_0in96_rgb
from PIL import Image,ImageDraw,ImageFont
logging.basicConfig(level=logging.DEBUG)

try:
    disp = OLED_0in96_rgb.OLED_0in96_rgb()

    logging.info("\r 0.96inch rgb OLED ")
    # Initialize library.
    disp.Init()
    # Clear display.
    logging.info("clear display")
    # disp.clear()
    disp.clear_color(0x8410)

    # Create blank image for drawing.
    image1 = Image.new('RGB', (disp.height, disp.width), 0)
    draw = ImageDraw.Draw(image1)
    font = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 12)
    font1 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 18)
    font2 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 24)
    logging.info ("***draw line")
    draw.line([(0,0),(0,63)], fill = "RED")
    draw.line([(0,0),(127,0)], fill = "RED")
    draw.line([(127,0),(127,63)], fill = "RED")
    draw.line([(0,63),(127,63)], fill = "RED")
    logging.info ("***draw text")
    draw.text((20,0), 'Waveshare ', font = font1, fill = "BLUE")
    draw.text((20,28), u'微雪电子 ', font = font2, fill = "MAGENTA")
    image1 = image1.rotate(270, expand = 1)
    disp.ShowImage(disp.getbuffer(image1))
    time.sleep(3)


    logging.info ("***draw rectangle")
    image1 = Image.new("RGB", (disp.width, disp.height), "BLACK")
    draw = ImageDraw.Draw(image1)
    draw.line([(0,8), (64,8)],   fill = "RED",    width = 16)
    draw.line([(0,24),(64,24)],  fill = "GREEN", width = 16)
    draw.line([(0,40),(64,40)],  fill = "BLUE",  width = 16)
    draw.line([(0,56),(64,56)],  fill = "RED",   width = 16)
    draw.line([(0,72),(64,72)],  fill = "YELLOW",   width = 16)
    draw.line([(0,88),(64,88)],  fill = "MAGENTA",width = 16)
    draw.line([(0,104),(64,104)],  fill = "LIME",width = 16)
    disp.ShowImage(disp.getbuffer(image1))
    time.sleep(3)

    logging.info ("***draw image")
    Himage2 = Image.new('RGB', (disp.width, disp.height), 0)  # 0: clear the frame
    bmp = Image.open(os.path.join(picdir, '0in96_rgb.bmp'))
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