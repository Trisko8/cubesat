#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d as m3d

xr=[-248.781*0.16, -248.781*-0.16]
yr=[-227.092*0.16, -227.092*-0.16]
zr=[369.51*0.16, 369.51*-0.16]

# Drawing.
ax = m3d.Axes3D(plt.figure())
ax.scatter3D(xr, yr, zr, c='none')
ax.plot3D(xr,yr,zr, c='r', label="P = " + str("[-248.781") + ", " + str("-227.092") + ", " + str("369.51]") + " + " + "t*" + str("[0.498") + str(", ") + str("0.454") + str(", ") + str("-0.739]"))
ax.legend()
ax.set_xlabel('$x$' + ' (mm)')
ax.set_ylabel('$y$' + ' (mm)')
ax.set_zlabel('$z$' + ' (mm)')
ax.set_xlim(-60,60)
ax.set_ylim(-60,60)
ax.set_zlim(-60,60)

plt.savefig('real_trajectory.png')
plt.show()