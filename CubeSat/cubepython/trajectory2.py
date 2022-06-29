#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d as m3d
import math 

def magnitude(vector): 
    return math.sqrt(sum(pow(element, 2) for element in vector)) 

def lineal(X,m,n):
	return m*X+n

def normaliza(v, tol=1e-6):
    norma = np.linalg.norm(v)
    if norma < tol:
        raise ValueError('La norma del vector es inferior a la tolerancia {}.'.format(tol))
    v_norm = v/norma  # Al usar np.linalg.norm() v_norm es un numpy.ndarray
    return v_norm

def angulo(v1, v2):
    prod_esc = np.dot(v1, v2)
    norma_v1 = np.linalg.norm(v1)
    norma_v2 = np.linalg.norm(v2)

    angulo = np.arccos(np.clip(prod_esc/(norma_v1*norma_v2), -1, 1))
    return angulo

def distancia_entre_puntos(p1, p2):  # Versión solo válida para numpy arrays
    dist = np.linalg.norm(p1-p2)  # p1-p2 no está definido para tuplas o listas
    return dist

def plano_tres_puntos(p1, p2, p3, tol=1e-3):
    dist12 = distancia_entre_puntos(p1, p2)
    dist13 = distancia_entre_puntos(p1, p3)
    dist23 = distancia_entre_puntos(p2, p3)

    if dist12 < tol or dist13 < tol or dist23 < tol:
        raise ValueError('Distancia entre puntos menor que la tolerancia {}.'.format(tol))

    # Producto vectorial para A B C
    # |  i       j       k    |
    # |v_12[0] v_12[1] v_12[2]|
    # |v_13[0] v_13[1] v_13[2]|

    v12 = p1 - p2
    v13 = p1 - p3

    n = normaliza(np.cross(v12, v13))

    D = -np.dot(n, p1)

    return n, D

def interseccion_recta_plano(recta, plano, tol=0.1):
    ang = angulo(recta[1], plano[0])

    if np.abs(ang-np.pi/2) < tol:
        raise ValueError('La recta y el plano son casi paralelos según tolerancia {}.'.format(tol))

    lamb = -(np.dot(recta[0], plano[0])+plano[1])/np.dot(recta[1], plano[0])

    return recta[0] + lamb*recta[1]

def proyeccion_punto_recta(recta, punto):
    plano = (recta[1], -np.dot(recta[1], punto))
    p_r = interseccion_recta_plano(recta, plano)

    return p_r

fichero=np.loadtxt("xyz_2",dtype='float',comments='#',delimiter=None, skiprows=0, usecols=None, encoding="utf8")
x, y, z=fichero[:,0], fichero[:,1], fichero[:,2]

data = np.concatenate((x[:, np.newaxis], 
                       y[:, np.newaxis], 
                       z[:, np.newaxis]), 
                      axis=1)

n=len(fichero)
# Perturb with some Gaussian noise
data += np.random.normal(size=data.shape) * 0.4

# Calculate the mean of the points, i.e. the 'center' of the cloud
datamean = data.mean(axis=0)

# Do an SVD on the mean-centered data.
uu, dd, vv = np.linalg.svd(data - datamean)

# Now vv[0] contains the first principal component, i.e. the direction
# vector of the 'best fit' line in the least squares sense.

# Now generate some points along this best fit line, for plotting.
linepts = vv[0] * np.mgrid[-90:90:2j][:, np.newaxis]

# shift by the mean to get the line in the right place
linepts += datamean

#Error
p0 = datamean
direction = normaliza(vv[0, :])
d = direction
pos=np.array([])

i=0
while i<n:
    proy = proyeccion_punto_recta((p0, d), fichero[i])
    pos = np.append(pos,proy)
    i+=1

position = np.array_split(pos, n)

err_rel2 = np.loadtxt("err_rel2",dtype='float',comments='#',delimiter=None, skiprows=0, usecols=None, encoding="utf8")
x, y, z=err_rel2[:,0], err_rel2[:,1], err_rel2[:,2]
    
#Angle 
delta_x=np.sqrt(np.sum(np.square(err_rel2[:,0]**2))) 
delta_y=np.sqrt(np.sum(np.square(err_rel2[:,1]**2))) 
delta_z=np.sqrt(np.sum(np.square(err_rel2[:,2]**2))) 
    
delta_a=np.sqrt(np.sum(np.square(np.multiply(np.divide(fichero[:,1], np.square(fichero[:,0])+np.square(fichero[:,1])), err_rel2[:, 0]))) + np.sum(np.square(np.multiply(np.divide(fichero[:,1], np.square(fichero[:,0])+np.square(fichero[:,1])), err_rel2[:, 1]))))
delta_e=np.sqrt(np.sum(np.square(np.multiply(np.divide(fichero[:,1], np.square(fichero[:,2])+np.square(fichero[:,1])), err_rel2[:, 1]))) + np.sum(np.square(np.multiply(np.divide(fichero[:,2], np.square(fichero[:,2])+np.square(fichero[:,1])), err_rel2[:, 2]))))

a = np.degrees(np.arctan(d[0]/d[1]))
e = np.degrees(np.arctan(d[2]/d[1]))

print("Azimuth = " + str("%.2f" % a) + u"\u00B1" + str("%.2f" % delta_a))
print("Elevation = " + str("%.3f" % e) + u"\u00B1" + str("%.3f" % delta_e))

#Distance of each point to the line
direction = vv[0, :]
distance=np.array([])
h=0

i=0
while(i<len(data)):
    s = magnitude(np.cross(fichero[i]-position[i],d))/magnitude(d)
    distance=np.append(distance,s)
    h+=s
    i+=1

print(distance)
print("%.2f" % h)

# Verify that everything looks right.
ax = m3d.Axes3D(plt.figure())
ax.scatter3D(*fichero.T)
ax.plot3D(*linepts.T, label="P = " + str("[") + str("%.2f" % p0[0]) + str(", ") + str("%.2f" % p0[1]) + str(", ") + str("%.2f" % p0[2]) + str("]") +'+' +'t*' + str("[") + str("%.2f" % d[0]) + str(", ") + str("%.2f" % d[1]) + str(", ") + str("%.2f" % d[2]) + str("]"))
ax.legend()
ax.set_xlabel('$x$' + ' (mm)')
ax.set_ylabel('$y$' + ' (mm)')
ax.set_zlabel('$z$' + ' (mm)')
for i in np.arange(0, len(fichero)):
    ax.plot([fichero[i, 0]+err_rel2[i, 0], fichero[i, 0]-err_rel2[i, 0]], [fichero[i, 1], fichero[i, 1]], [fichero[i, 2], fichero[i, 2]], marker="_")
    ax.plot([fichero[i, 0], fichero[i, 0]], [fichero[i, 1]+err_rel2[i, 1], fichero[i, 1]-err_rel2[i, 1]], [fichero[i, 2], fichero[i, 2]], marker="_")
    ax.plot([fichero[i, 0], fichero[i, 0]], [fichero[i, 1], fichero[i, 1]], [fichero[i, 2]+err_rel2[i, 2], fichero[i, 2]-err_rel2[i, 2]], marker="_")
plt.savefig('trajectory2.png')
plt.show()