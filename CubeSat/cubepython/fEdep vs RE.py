# -*- coding: utf-8 -*-
#https://matplotlib.org/index.html
#https://unipython.com/matplotlib-funciones-principales/
from numpy import *
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from math import pi

# CURVAS PARA AJUSTE
def lineal_0(X,m):
	return m*X
def lineal(X,m,n):
	return m*X+n

# FUNCIONES
def ajusta (g, x, y, p0):
	nx = len(x)
	p, cov, infodict, errmsg, ier = curve_fit(g, x, y, p0, full_output=True)
	E = (infodict['fvec']**2).sum()
	r2 = 1-E/((y-y.mean())**2).sum() # r2 del ajuste
	perr = sqrt(diag(cov)) # errores estándar de los parámetros
	return p, perr, r2, E

#FICHERO
fichero=loadtxt("fEdep",dtype='float',comments='#',delimiter=None, skiprows=0, usecols=None)
x, y=fichero[:,0], fichero[:,1]
ajuste=ajusta(lineal,x[:],y[:],None)
valores=polyfit(x,y,1)
a,b=valores[0],valores[1]

#GRÁFICA
plt.plot(x[:],a*x[:]+b,'-',label=str(a) + 'x' + ' + ' + str(b))
plt.plot(x[:],y[:],'bo')
plt.xlabel('Energía real (MeV)'); plt.ylabel('Energía depositada (MeV)')
plt.title('Energía real vs energía depositada')
plt.legend()
plt.show()