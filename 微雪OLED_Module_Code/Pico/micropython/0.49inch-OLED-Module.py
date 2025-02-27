from machine import Pin,I2C
import framebuf
import time


class OLED_0inch49(framebuf.FrameBuffer):
    def __init__(self,i2c_num=1,i2c_scl=7,i2c_sda=6,i2c_freq=1000000):
        
        self.width  = 64
        self.height = 32
        
        
        self.rotate = 180 #only 0 and 180

        self.olde_addr = 0x3c

        self.i2c = I2C(id=i2c_num, scl=Pin(i2c_scl), sda=Pin(i2c_sda), freq=i2c_freq)

        self.temp = bytearray(2)
        self.buffer = bytearray(self.width * self.height//2)

        super().__init__(self.buffer, self.width, self.height, framebuf.MONO_VLSB)
        self.init_display()
        
        self.white =   0xffff
        self.black =   0x0000
        
    def write_cmd(self, cmd):
        self.temp[0] = 0x00 
        self.temp[1] = cmd
        self.i2c.writeto(self.olde_addr, self.temp)

    def write_data(self, buf):
        self.temp[0] = 0x40 
        self.temp[1] = buf
#         self.i2c.writeto(self.olde_addr, b'\x40'+buf)
        self.i2c.writeto(self.olde_addr, self.temp)
        
    def init_display(self):
        """Initialize dispaly"""  
        
        self.write_cmd(0xAE); # display off

        self.write_cmd(0x00); # set lower column address 
        self.write_cmd(0x12); # set higher column address 

        self.write_cmd(0x00); # set display start line 

        self.write_cmd(0xB0); # set page address 


        self.write_cmd(0x81); # contract control 
        self.write_cmd(0x4f); # 128 

        self.write_cmd(0xA1); # set segment remap 

        self.write_cmd(0xA6); # normal / reverse 

        self.write_cmd(0xA8); # multiplex ratio 
        self.write_cmd(0x1F); # duty = 1/32 


        self.write_cmd(0xC8); # Com scan direction 

        self.write_cmd(0xD3); # set display offset 
        self.write_cmd(0x00);

        self.write_cmd(0x20);
        self.write_cmd(0x01); # set Vertical Addressing Mode 

        self.write_cmd(0xD5); # set osc division 
        self.write_cmd(0x80);

        self.write_cmd(0xD9); # set pre-charge period 
        self.write_cmd(0xf1);

        self.write_cmd(0xDA); # set COM pins 
        self.write_cmd(0x12);

        self.write_cmd(0xdb); # set vcomh 
        self.write_cmd(0x40);

        self.write_cmd(0x8d); # set charge pump enable 
        self.write_cmd(0x14);

        self.write_cmd(0xAF); # display ON 
        
    def show(self):          
        for i in range(0, 4):
            self.write_cmd(0x22)            
            self.write_cmd(0x00+i) # set start page address
            self.write_cmd(0x00+i) # set end page address
            self.write_cmd(0x21)
            self.write_cmd(0x20) # set low column address
            self.write_cmd(0x5f) # set high column address
            # write data #
            for j in range(0, self.width):
                self.write_data(self.buffer[j+self.width*i])
        return

          
if __name__=='__main__':

    OLED = OLED_0inch49()
    OLED.fill(0x00)
    OLED.text("OLED0.49",0,1,OLED.white)
    OLED.text("64x32Px",4,12,OLED.white)
    OLED.text("SSD1315",4,23,OLED.white)  
    OLED.show()
    time.sleep(1)
    while True:
        pass

