import numpy as np
from random import *
from PIL import Image
import cv2

def sred(a):
    return int(sum(a)/3)


def answer(a):
    f.write(str(int(a[0] / 2.55)) + " ")
    f.write(str(int(a[1] / 2.55)) + " ")
    f.write(str(int(a[2] / 2.55)) + " ")

a = int(input("Введите цвет по крассному каналу: "))
b = int(input("Введите цвет по зеленому каналу: "))
c = int(input("Введите цвет по синему каналу: "))

with open("user_primers.csv", "w") as f:
    for item in range(1):
        box_random = (a, b, c)

        image = Image.new("RGB", (28, 28), box_random)
        answer(box_random)

        image.save("result.jpg")
        image = cv2.imread("result.jpg")
        b, g, r = cv2.split(image)
        cv2.imwrite('blue.jpg', b)
        cv2.imwrite('green.jpg', g)
        cv2.imwrite('red.jpg', r)
        merge_image = cv2.merge([g,b,r])
        cv2.waitKey(0)

        image_red = Image.open("red.jpg")
        image_green = Image.open("green.jpg")
        image_blue = Image.open("blue.jpg")
        image = Image.new("RGB", (28, 84), (255,255,255))
        image.paste(image_red)
        image.paste(image_green, (0, 28))
        image.paste(image_blue, (0, 56))
        
        for i in range(0, 84):
            for j in range(0, 28):
                f.write(str(sred(image.getpixel((j,i)))) + " ")
        
        f.write("\n")
        image.save("resultation.png")

# with open("training_30k.csv", "r") as k:
#     p = k.readline().split(" ")
#     f = p[3:]
#     print(f)
#     print(f.count("149"))
#     print(f.count("73"))
#     print(f.count("2"))
#     for i in range(len(f)):
#         if i+1 % 28 == 0:
#             print("\n")
#         print(f[i], end=" ")
        