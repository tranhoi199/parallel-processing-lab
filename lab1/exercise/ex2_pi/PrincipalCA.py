#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Sep 18 20:00:55 2019

@author: macbook
"""

import numpy as np 
from scipy import misc 
np.random.seed(1)
import imageio
#filename structure 
path = './YALE/unpadded/'
ids = range(1,16)
states = ['centerlight', 'glasses', 'happy', 'leftlight','noglasses', 'normal', 'rightlight', 'sad','sleepy','surprised','wink']
prefix = 'subject'
surfix = '.pgm'

#data demension 
h = 116 #height
w = 98 #width 
D = h*w 
N = len(states)*15 
K = 100 

#collect all data 

X = np.zeros((D, N))
cnt = 0

for person_id in range(1, 16):
	for state in states:
		fn = path + prefix +str(person_id).zfill(2) + '.' + state + surfix
		X[:, cnt] = imageio.imread(fn).reshape(D)
		cnt +=1

#Doing PCA, not that each row is a datapoint 
from sklearn.decomposition import PCA 
pca = PCA(n_components = K) #K =100
pca.fit(X.T)

U = pca.components_.T

import matplotlib.pyplot as plt 
for i in range(U.shape[1]):
	plt.axis('off')
	f1 = plt.imshow(U[:, i].reshape(116,98), interpolation = 'nearest')
	f1.axes.get_xaxis().set_visible(False)
	f1.axes.get_yaxis().set_visible(False)

	plt.gray()
	fn = 'eigenface' + str(i).zfill(2) + '.png'
	plt.savefig(fn, bbox_inches = 'tight', pad_inches = 0)
for person_id in range(1, 7):
    for state in ['centerlight']:
        fn = path + prefix + str(person_id).zfill(2) + '.' + state + surfix
        im = imageio.imread(fn)
        plt.axis('off')
#         plt.imshow(im, interpolation='nearest' )
        f1 = plt.imshow(im, interpolation='nearest')
        f1.axes.get_xaxis().set_visible(False)
        f1.axes.get_yaxis().set_visible(False)
        plt.gray()
        fn = 'ori' + str(person_id).zfill(2) + '.png'
        plt.savefig(fn, bbox_inches='tight', pad_inches=0)
        plt.show()
        # reshape and subtract mean, don't forget 
        x = im.reshape(D, 1) - pca.mean_.reshape(D, 1)
        # encode
        z = U.T.dot(x)
        #decode
        x_tilde = U.dot(z) + pca.mean_.reshape(D, 1)

        # reshape to orginal dim
        im_tilde = x_tilde.reshape(116, 98)
        plt.axis('off')
#         plt.imshow(im_tilde, interpolation='nearest' )
        f1 = plt.imshow(im_tilde, interpolation='nearest')
        f1.axes.get_xaxis().set_visible(False)
        f1.axes.get_yaxis().set_visible(False)
        plt.gray()
        fn = 'res' + str(person_id).zfill(2) + '.png'
        plt.savefig(fn, bbox_inches='tight', pad_inches=0)
        plt.show()