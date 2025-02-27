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
from waveshare_OLED import OLED_0in49
from PIL import Image,ImageDraw,ImageFont
logging.basicConfig(level=logging.DEBUG)

try:
    disp = OLED_0in49.OLED_0in49()
    logging.info("\r 0.49inch OLED Module ")
    # Initialize library.
    disp.Init()
        
    # Clear display.
    logging.info("clear display")
    disp.clear()
    
    # Create blank image for drawing.
    image1 = Image.new('1', (disp.width, disp.height), "WHITE")
    draw = ImageDraw.Draw(image1)
    font1 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 12)
    font2 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 12)
    logging.info ("***draw line")
    draw.line([(0,0),(63,0)], fill = 0)
    draw.line([(0,0),(0,31)], fill = 0)
    draw.line([(0,31),(63,31)], fill = 0)
    draw.line([(63,0),(63,31)], fill = 0)
    logging.info ("***draw text")
    draw.text((3,0), 'Waveshare ', font = font1, fill = 0)
    draw.text((3,12), u'微雪电子 ', font = font2, fill = 0)
    image1=image1.rotate(0)  
    disp.ShowImage(disp.getbuffer(image1))
    time.sleep(3)
    
    logging.info ("***draw image")
    Himage2 = Image.new('1', (disp.width, disp.height), 255)  # 255: clear the frame
    bmp = Image.open(os.path.join(picdir, '0in49.bmp'))
    Himage2.paste(bmp, (0,0))
    Himage2=Himage2.rotate(0)
    disp.ShowImage(disp.getbuffer(Himage2))  
    time.sleep(3)
    disp.clear()

except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    OLED_0in49.config.module_exit()
    exit()