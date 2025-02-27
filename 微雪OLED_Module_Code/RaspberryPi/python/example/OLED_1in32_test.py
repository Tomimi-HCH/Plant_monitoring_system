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
from waveshare_OLED import OLED_1in32
from PIL import Image,ImageDraw,ImageFont
logging.basicConfig(level=logging.DEBUG)

try:
    disp = OLED_1in32.OLED_1in32()

    logging.info("\r 1.32inch OLED ")
    # Initialize library.
    disp.Init()
    # Clear display.
    logging.info("clear display")
    disp.clear()

    while 1:
        # Create blank image for drawing.
        image1 = Image.new('L', (disp.height, disp.width), 0)
        draw = ImageDraw.Draw(image1)
        font = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 12)
        font1 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 18)
        font2 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 24)
        logging.info ("***draw line")
        draw.line([(0,0),(95,0)], fill = 15)
        draw.line([(0,0),(0,127)], fill = 15)
        draw.line([(0,127),(95,127)], fill = 15)
        draw.line([(95,0),(95,127)], fill = 15)
        logging.info ("***draw text")
        draw.text((20,2), 'Hello', font = font1, fill = 13)
        draw.text((20,18), 'World ', font = font1, fill = 5)
        draw.text((20,44), u'微雪 ', font = font2, fill = 1)
        draw.text((20,66), u'电子 ', font = font2, fill = 9)
        image1 = image1.rotate(0)
        disp.ShowImage(disp.getbuffer(image1))
        time.sleep(3)

        logging.info ("***draw rectangle")
        image1 = Image.new('L', (disp.width, disp.height), 0)
        draw = ImageDraw.Draw(image1)
        for i in range(0, 16):
            draw.rectangle([(8*i, 0), (8*(i+1), 96)], fill = i)
        disp.ShowImage(disp.getbuffer(image1))
        time.sleep(3)

        logging.info ("***draw image")
        Himage2 = Image.new('L', (disp.width, disp.height), 0)  # 0: clear the frame
        bmp = Image.open(os.path.join(picdir, '1in32.bmp'))
        Himage2.paste(bmp, (0,0))
        disp.ShowImage(disp.getbuffer(Himage2)) 
        time.sleep(3)    
    disp.clear()

except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    disp.module_exit()
    exit()