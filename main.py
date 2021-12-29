#!/usr/bin/env python 
# -*- coding: utf-8 -*-

import board
import neopixel
import time
import asyncio
from datetime import datetime
from multiprocessing import Process, Value

from aiogram import Bot, types
from aiogram.dispatcher import Dispatcher
from aiogram.utils import executor

from config import TOKEN


pixels = neopixel.NeoPixel(board.D18,100)

bot = Bot(token=TOKEN)
dp = Dispatcher(bot)

colors = {"❤️": "Красный", "🧡": "Оранжевый", "💛": "Желтый",
        "💚": "Зеленый", "💙": "Синий", "💜": "Фиолетовый",
        "🖤": "Черный", "🤍": "Белый", "🤎": "Коричневый"}

ind_colors = {0: "Красный", 1: "Оранжевый", 2: "Желтый",
            3: "Зеленый", 4: "Синий", 5: "Фиолетовый", 
            6: "Черный", 7: "Белый", 8: "Коричневый"}

colors_ind = {}
for k, v in ind_colors.items():
    colors_ind[v] = k

rgb = {"Красный": (255, 0, 0), "Оранжевый": (255, 165, 0), "Желтый": (255, 255, 0),
        "Зеленый": (0, 128, 0), "Синий": (0, 0, 255), "Фиолетовый": (128, 0, 128),
        "Черный": (0, 0, 0), "Белый": (255, 255, 255), "Коричневый": (165, 42, 42)}


nums = {0: [1, 2, 3, 4, 5, 6], 1: [1, 6], 2: [1, 2, 4, 5, 7], 3: [1, 2, 5, 6, 7], 4: [1, 3, 6, 7], 5: [2, 3, 5, 6, 7], 6: [2, 3, 4, 5, 6, 7], 7: [1, 2, 6], 8: [1, 2, 3, 4, 5, 6, 7], 9:[1, 2, 3, 5, 6, 7]}
look = 0
pr = 0

def change_digit(t):
    num = nums[t]
    
    '''
    for i in range(100):
        #print('i', i)
        pixels[i] = (0, 0, 0)
    '''
    current_color = 0
    with open('color.txt', 'r') as f:
        line = f.read()
        
        if len(line):
            current_color = int(line[0])


    for i in range(1, 8):
        for j in range(14):
            if i in num:
                #print(i)
                pixels[(i - 1) * 14 + j] = rgb[ind_colors[current_color]]
            else:
                pixels[(i - 1) * 14 + j] = (0, 0, 0)
    
    '''
    for i in num:
        print('ii', i)
        for j in range(0, 14):
            pixels[(i - 1) * 14 + j] = rgb[current_color]
    '''

def change(root=0):
    print('change')
    global pr

    t = datetime.now().strftime('%M')
    t = int(t) % 10
    if 1 or t != pr or root:
        print('t', t)
        change_digit(t)
        pr = t


@dp.message_handler(commands=['start'])
async def process_start_command(message):
    await message.reply("Привет!\nНапиши мне что-нибудь!")


@dp.message_handler(content_types=['text'])
async def main_logic(msg):
    global look
    global current_color
    '''
    if look != 0:
        look = 1
        await asyncio.sleep(1)
        
    look = 1
    '''
    global pr
    if msg.text >= '0' and msg.text <= '9':
        num = int(msg.text)
        #pr = num 
        change_digit(num)    
        print("ok") 
    elif msg.text in colors.keys():
        #current_color.value = colors_ind[colors[msg.text]]
        current_color = colors_ind[colors[msg.text]]

        with open('color.txt', 'w') as f:
            f.write(str(current_color))
        
        change(1)
        print(current_color)
        #for i in range(0, 100):
        #    pixels[i] = rgb[c]
    
    #await asyncio.sleep(5)
    look = 0
    await bot.send_message(msg['from']['id'], 'Цвет изменен')


def start_bot():
    executor.start_polling(dp)


def timer():
    global pr
    while True:
        if True:
            #look = 2
            change()
            '''
            t = datetime.now().strftime('%M')
            t = int(t) % 10
            if t != pr:
                print('t', t)
                change_digit(t)
                pr = t
            '''
            #if look == 2:
            #look = 0
            

        #await ayncio.sleep(1)
        time.sleep(5)


if __name__ == '__main__':
    try:
        p1 = Process(target=start_bot)
        p1.start()

        p2 = Process(target=timer)
        p2.start()

        p1.join()
        p2.join()
        

        #loop = asyncio.get_event_loop()
        #asyncio.ensure_future()
    except Exception as e:
        print(e)
    
