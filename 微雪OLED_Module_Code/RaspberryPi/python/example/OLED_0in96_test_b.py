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
import math
import traceback
from waveshare_OLED import OLED_0in96
from PIL import Image,ImageDraw,ImageFont
logging.basicConfig(level=logging.DEBUG)
try:
    disp = OLED_0in96.OLED_0in96()

    logging.info("\r 0.96inch OLED ")
    # Initialize library.
    disp.Init()
    # Clear display.
    logging.info("clear display")
    disp.clear()

    # Create blank image for drawing.
    image1 = Image.new('1', (disp.width, disp.height), "WHITE")
    draw = ImageDraw.Draw(image1)
    font1 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 18)
    font2 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 24)
    logging.info ("***draw line")
    draw.line([(0,0),(127,0)], fill = 0)
    draw.line([(0,0),(0,63)], fill = 0)
    draw.line([(0,63),(127,63)], fill = 0)
    draw.line([(127,0),(127,63)], fill = 0)
    logging.info ("***draw text")
    draw.text((20,0), 'Waveshare ', font = font1, fill = 0)
    draw.text((20,24), u'微雪电子 ', font = font2, fill = 0)
    image11 = image1.rotate(0) 
    disp.ShowImage(disp.getbuffer(image11))
    time.sleep(3)
    
    logging.info ("***draw image")
    Himage2 = Image.new('1', (disp.width, disp.height), 255)  # 255: clear the frame
    bmp = Image.open(os.path.join(picdir, '0in96.bmp'))
    Himage2.paste(bmp, (0,0))
    Himage2=Himage2.rotate(0)     
    disp.ShowImage(disp.getbuffer(Himage2))  
    time.sleep(3)
    disp.clear()
    
    font = ImageFont.load_default()
    width = disp.width
    height = disp.height
    text = 'Waveshare 0.96inch OLED Module DISPLAY. THIS IS A SCROLLER DEMO!!!'
    maxwidth, unused = draw.textsize(text, font=font)

    # Set animation and sine wave parameters.
    amplitude = height/4
    offset = height/2
    velocity = -1
    startpos = width
    pos = startpos
    
    t_0=t_1=i=i_=0
    while 1:
        t_0=int(time.time()%10)
        draw.rectangle((0,0,width,height), outline=255, fill=255)
        draw.text((32,0), str(i_) , font=font, fill=0)
        draw.text((0, 0), 'FPS:', font=font, fill=0)
        # Enumerate characters and draw them offset vertically based on a sine wave.
        x = pos
        for i, c in enumerate(text):
            # Stop drawing if off the right side of screen.
            if x > width:
                break
            # Calculate width but skip drawing if off the left side of screen.
            if x < -10:
                char_width, char_height = draw.textsize(c, font=font)
                x += char_width
                continue
            # Calculate offset from sine wave.
            y = offset+math.floor(amplitude*math.sin((x+pos)/float(width)*2.0*math.pi))
            # Draw text.
            draw.text((x, y), c, font=font, fill=0)
            # Increment x position based on chacacter width.
            char_width, char_height = draw.textsize(c, font=font)
            x += char_width+1
        # Draw the image buffer.
        image11 = image1.rotate(0)
        disp.ShowImage(disp.getbuffer(image11))
        # Move position for next frame.
        pos += velocity
        # Start over if text has scrolled completely off left side of screen.
        if pos < -maxwidth:
            pos = startpos
        # Pause briefly before drawing next frame.
        # time.sleep(0.1)
        if t_0 != t_1 :
            i_=i
            i=0
            t_1=t_0
        else:
            i+=1
except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    disp.module_exit()
    exit()
