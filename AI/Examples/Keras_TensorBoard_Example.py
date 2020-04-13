#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Feb 28 23:24:06 2020


This is the Fashion MNIST example
"""

import tensorflow as tf
#from tensorflow import keras
import numpy as np
#import datetime

mnist = tf.keras.datasets.mnist

(x_train, y_train),(x_test, y_test) = mnist.load_data()
x_train, x_test = x_train / 255.0, x_test / 255.0

#create a tensorboard log directory
#log_dir="logs/fit/" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S") # defualt
log_dir = "logs/fit/keras_tensorboard_example"
tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)


# Creates a file writer for the log directory.
file_writer = tf.summary.create_file_writer(log_dir)

# Reshape the image for the Summary API.
img = np.reshape(x_train[0], (-1, 28, 28, 1))

# Using the file writer, log the reshaped image.
with file_writer.as_default():
  tf.summary.image("Training data", img, step=0)
  

def create_model():
  return tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape=(28, 28)),
    tf.keras.layers.Dense(512, activation='relu'),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(10, activation='softmax')
  ])


model = create_model()
model.summary()
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

model.fit(x=x_train, 
          y=y_train, 
          epochs=50, 
          validation_data=(x_test, y_test), 
          callbacks=[tensorboard_callback])


#save model
model.reset_metrics()
model.save(log_dir+'/fashion_mnist.h5')  #default is HDF5 format
#model.save(log_dir+'/tf_Models/', save_format='tf')  #saved in tf SaveModel format


