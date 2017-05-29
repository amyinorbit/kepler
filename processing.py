#!/usr/bin/env python
# -*- coding: utf-8 -*-
import PIL
import sys
import argparse
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

radius = 6371e3

#print('hello')


def plot_earth(p):
    lons = np.linspace(-180, 180, 180) * np.pi/180
    lats = np.linspace(-90, 90, 180)[::-1] * np.pi/180

    xm = radius * np.outer(np.cos(lons), np.cos(lats)).T
    ym = radius * np.outer(np.sin(lons), np.cos(lats)).T
    zm = radius * np.outer(np.ones(np.size(lons)), np.sin(lats)).T
    p.plot_surface(xm, ym, zm, rstride=10, cstride=10, color='w', alpha=1, shade=False, zorder=0.5, linewidth=0.4)


data = np.genfromtxt('/tmp/kepler-out.csv', delimiter=',', names=True)
time = data['time']
x = data['x']
y = data['y']
z = data['z']
ix = data['ix']
iy = data['iy']
iz = data['iz']
lat = data['lat']
lon = data['lon']

plt.figure()
plt.title('Orbit')


plot1 = plt.gca(projection='3d')
plot1.margins(0.05)

# coordinates of the image - don't know if this is entirely accurate, but probably close

plot1.plot(x, y, z, 'r', label='trajectory', linewidth=0.4, zorder=0.1)
plot1.plot(ix, iy, iz, 'b', label='trajectory', linewidth=0.4, zorder=0.1)
plot_earth(plot1)
plot1.set_aspect('equal', adjustable='box')

l = np.amax([np.amax(np.abs(x)), np.amax(np.abs(y)), np.amax(np.abs(z))])

plot1.auto_scale_xyz([-l, l], [-l, l], [-l, l])

#plt.savefig('/Users/cesar/Desktop/trajectory.pdf')


plt.show()
