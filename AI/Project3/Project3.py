# -*- coding: utf-8 -*-
"""
Created on Wed Apr 15 16:57:30 2020

@author: Devin Hopkins
4190350

File for Project 3
"""

# Imports
import os
import tensorflow as tf
from tensorflow import keras
from tensorflow.python.keras.callbacks import TensorBoard
from tensorflow.python.keras.datasets import cifar10
from tensorflow.python.keras.preprocessing.image import ImageDataGenerator
from tensorflow.python.keras.models import Sequential
from tensorflow.python.keras.layers import Dense, Dropout, Activation, Flatten, BatchNormalization
from tensorflow.python.keras.layers import Conv2D, MaxPooling2D
from tensorflow.python.keras import regularizers

# Global Variables
DISPLAY_IMPORTANT_VARIABLES = True # True if variables that help with
#    understanding what is going on during execution should be displayed
DISPLAY_DEBUG_VARIABLES = True # True if the variables that help with
#    understanding the dataset (debugging) should be displayed
SAVE_DIRECTORY_BASE = os.path.join(os.getcwd(), 'logs\\') # Where the log will be
#    saved to
NUM_OF_CLASSES = 10 # Must remain at 10 for this data set

# This function takes two integers (min, max) and returns an integer that was
# entered by the user that is in between the min and max, inclusive. It also
# takes a string which is display to the user as the prompt for their input
def getNumInRange(min, max, inputString):    
    # The error string that the user will see if they enter the information
    # wrong
    errorString = "That was not an integer between " + str(min) + " and "
    errorString += str(max) + ".\nPlease enter a proper integer."
    
    # Stays false until we have correct data
    haveCorrectData = False
    
    # How we will store the integer the user gives us
    number = -1
    
    # Going through and getting the correct data
    while(not haveCorrectData):
        try:
            number = int(input(inputString))
            haveCorrectData = True
        except:
            haveCorrectData = False
        
        if (haveCorrectData):
            if (number >= min and number <= max):
                haveCorrectData = True
            else:
                haveCorrectData = False
        
        if (not haveCorrectData):
            print(errorString)
    
    # Returning the number
    return number

# This creates a Conv2D model using the almost same layers as the example given
# at the official Keras website
# (found here: https://keras.io/examples/cifar10_cnn/)
# I have added some layers to improve upon the example
def performMyExample(data_aug, batch, epoch, dir_name, mod_name):
    # Defining some local constants
    #
    # True yields better results (see below for why)
    USE_DATA_AUGMENTATION = data_aug
    # The number of training examples used in each iteration
    BATCH_SIZE = batch
    # The number of times the model will work through the entire data set
    EPOCHS = epoch
    # The name within the log directory where this model will be saved
    DIRECTORY_NAME = dir_name
    # The specific model name given to the model that will be generated in this
    # function
    MODEL_NAME = mod_name
    # Combining the base save directory with the specific save directory to
    # form the save directory for the model that will be generated
    SAVE_DIRECTORY = os.path.join(SAVE_DIRECTORY_BASE, DIRECTORY_NAME)
    # The rate of decay
    DECAY = 1e-6

    # Creating the tensorboard so it can be used for callbacks
    tensorboard = TensorBoard(log_dir=SAVE_DIRECTORY, histogram_freq=1,
                              profile_batch=10000000000)
    
    # Creating the keras regulizer
    keras_regularizer = regularizers.l2(DECAY)

    # Getting the CIFAR-10 data set and splitting it into training and testing
    (x_train, y_train), (x_test, y_test) = cifar10.load_data()

    if (DISPLAY_DEBUG_VARIABLES):
        # The type of the training and testing sets
        print()
        print("x_train type:", type(x_train))
        print("x_test type:", type(x_test))
        print("y_train type:", type(y_train))
        print("y_test type:", type(y_test))

    if (DISPLAY_IMPORTANT_VARIABLES or DISPLAY_DEBUG_VARIABLES):
        # The shape of the numpy arrays
        print()
        print('x_train shape:', x_train.shape)
        print('x_test shape:', x_test.shape)
        print(x_train.shape[0], 'train samples')
        print(x_test.shape[0], 'test samples')
        print()
        print('y_train shape:', y_train.shape)
        print('y_test shape:', y_test.shape)
        print(y_train.shape[0], 'train samples')
        print(y_test.shape[0], 'test samples')

    # Convert class vectors to binary class matrices
    y_train = keras.utils.to_categorical(y_train, NUM_OF_CLASSES)
    y_test = keras.utils.to_categorical(y_test, NUM_OF_CLASSES)

    if (DISPLAY_IMPORTANT_VARIABLES or DISPLAY_DEBUG_VARIABLES):
        # The shape of the numpy arrays
        print()
        print("After reshaping:")
        print('y_train shape:', y_train.shape)
        print('y_test shape:', y_test.shape)
        print(y_train.shape[0], 'train samples')
        print(y_test.shape[0], 'test samples')

    # Creating a sequential model
    model = Sequential()
    
    model.add(Conv2D(32, (3, 3), padding='same', kernel_regularizer=keras_regularizer, input_shape=x_train.shape[1:]))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(Conv2D(32, (3, 3), kernel_regularizer=keras_regularizer))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(MaxPooling2D(pool_size=(2, 2)))
    
    model.add(BatchNormalization())
    
    model.add(Conv2D(32, (3, 3), kernel_regularizer=keras_regularizer))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(Dropout(0.25))
    
    model.add(BatchNormalization())
    
    model.add(Conv2D(64, (3, 3), padding='same', kernel_regularizer=keras_regularizer))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(Conv2D(64, (3, 3), kernel_regularizer=keras_regularizer))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(MaxPooling2D(pool_size=(2, 2)))
    
    model.add(BatchNormalization())
    
    model.add(Conv2D(32, (3, 3), kernel_regularizer=keras_regularizer))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(Dropout(0.25))
    
    model.add(BatchNormalization())
    
    model.add(Conv2D(32, (3, 3), kernel_regularizer=keras_regularizer))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(Flatten())
    
    model.add(BatchNormalization())
    
    model.add(Dense(512, kernel_regularizer=keras_regularizer))
    model.add(Activation('relu'))
    
    model.add(BatchNormalization())
    
    model.add(Dropout(0.5))
    
    model.add(BatchNormalization())
    
    model.add(Dense(NUM_OF_CLASSES, kernel_regularizer=keras_regularizer))
    model.add(Activation('softmax'))

    # Initiate the Adam Optimizer
    #opt = keras.optimizers.Adam(learning_rate=0.0001, decay=DECAY)
    opt = keras.optimizers.RMSprop(learning_rate=0.0001, decay=1e-6)

    # Now it's time to compile the model
    model.compile(loss='categorical_crossentropy', optimizer=opt,
              metrics=['accuracy'])
    
    x_train = x_train.astype('float32')
    x_test = x_test.astype('float32')
    x_train /= 255
    x_test /= 255

    # Not using data augmentation for the model
    if not USE_DATA_AUGMENTATION:
        model.fit(x_train, y_train, batch_size=BATCH_SIZE, epochs=EPOCHS,
              validation_data=(x_test, y_test), shuffle=True,
              callbacks=[tensorboard])
    # Using data augmentation for the model
    else:
        # This will do preprocessing and realtime data augmentation
        datagen = ImageDataGenerator(
                featurewise_center=False,  # set input mean to 0 over the
                # dataset
                samplewise_center=False,  # set each sample mean to 0
                featurewise_std_normalization=False,  # divide inputs by std of
                # the dataset
                samplewise_std_normalization=False,  # divide each input by its
                # std
                zca_whitening=False,  # apply ZCA whitening
                zca_epsilon=1e-06,  # epsilon for ZCA whitening
                rotation_range=0,  # randomly rotate images in the range
                # (degrees, 0 to 180)
                # randomly shift images horizontally (fraction of total width)
                width_shift_range=0.1,
                # randomly shift images vertically (fraction of total height)
                height_shift_range=0.1,
                shear_range=0.,  # set range for random shear
                zoom_range=0.,  # set range for random zoom
                channel_shift_range=0.,  # set range for random channel shifts
                # set mode for filling points outside the input boundaries
                fill_mode='nearest',
                cval=0.,  # value used for fill_mode = "constant"
                horizontal_flip=True,  # randomly flip images
                vertical_flip=False,  # randomly flip images
                # set rescaling factor (applied before any other
                # transformation)
                rescale=None,
                # set function that will be applied on each input
                preprocessing_function=None,
                # image data format, either "channels_first" or "channels_last"
                data_format=None,
                # fraction of images reserved for validation (strictly between
                # 0 and 1)
                validation_split=0.0)

        # Compute quantities required for feature-wise normalization
        datagen.fit(x_train)

        # Fit the model on the batches generated by datagen.flow()
        model.fit_generator(datagen.flow(x_train, y_train,
                batch_size=BATCH_SIZE), epochs=EPOCHS,
                validation_data=(x_test, y_test), workers=4,
                callbacks=[tensorboard])

    # Save model and weights
    if not os.path.isdir(SAVE_DIRECTORY):
        os.makedirs(SAVE_DIRECTORY)
    # Creating the new model path with the specific model name and saving it
    model_path = os.path.join(SAVE_DIRECTORY, MODEL_NAME)
    model.save(model_path)
    
    # Letting the user know where the model is saved at and what it's name is
    print('Saved trained model at %s ' % model_path)

    # Score trained model
    scores = model.evaluate(x_test, y_test, verbose=1)
    print('Test loss:', scores[0])
    print('Test accuracy:', scores[1])

# This function performs the example given by the official Keras website found
# at: https://keras.io/examples/cifar10_cnn/
#
# This version is completely filled with comments explaining what everything
# does (to the best of my ability). It is also configured to perform at the 2010
# basline (see link directly above). Note that the actual performance is done
# in the performKerasExample() function
def performBaselineKerasTest():
    # Defining the baseline variables
    #
    # Use data augmentation? [baseline = True]
    # The number of training examples used in each iteration [baseline = 32]
    # The number of times the model will work through the entire data set
    #     [baseline = 50]
    # The name within the log directory where this model will be saved
    # The specific model name given to the model that will be generated in this
    #     function (professor wants it to be cifar-10.h5)
    #
    # Performing the Keras Example using the baseline arguments
    performKerasExample(True, 32, 50, "keras_baseline\\", "cifar-10.h5")

# This creates a Conv2D model using the same layers as the example given at the
# official Keras website (found here: https://keras.io/examples/cifar10_cnn/)
def performKerasExample(data_aug, batch, epoch, dir_name, mod_name):
    # Defining some local constants
    #
    # True yields better results (see below for why)
    USE_DATA_AUGMENTATION = data_aug
    # The number of training examples used in each iteration
    BATCH_SIZE = batch
    # The number of times the model will work through the entire data set
    EPOCHS = epoch
    # The name within the log directory where this model will be saved
    DIRECTORY_NAME = dir_name
    # The specific model name given to the model that will be generated in this
    # function
    MODEL_NAME = mod_name
    # Combining the base save directory with the specific save directory to
    # form the save directory for the model that will be generated
    SAVE_DIRECTORY = os.path.join(SAVE_DIRECTORY_BASE, DIRECTORY_NAME)

    # Creating the tensorboard so it can be used for callbacks
    tensorboard = TensorBoard(log_dir=SAVE_DIRECTORY, histogram_freq=1,
                              profile_batch=10000000000)

    # Getting the CIFAR-10 data set and splitting it into training and testing
    #
    # The CIFAR-10 dataset is an established computer-vision dataset used for
    # recognition. It has 60,000 images, which are each 32x32 in size, and use
    # the RGB color system (keep these numbers in mind, as the shape of the
    # arrays will directly correlate to these numbers)
    (x_train, y_train), (x_test, y_test) = cifar10.load_data()

    if (DISPLAY_DEBUG_VARIABLES):
        # The type of the training and testing sets
        #
        # In this case, they are all numpy.ndarray
        print()
        print("x_train type:", type(x_train))
        print("x_test type:", type(x_test))
        print("y_train type:", type(y_train))
        print("y_test type:", type(y_test))

    if (DISPLAY_IMPORTANT_VARIABLES or DISPLAY_DEBUG_VARIABLES):
        # The shape of the numpy arrays
        #
        # For the x variables, they are 4 dimensional
        # 1D: The image (used to specify which image)
        # 2D: The width of the image (used to specify which column the pixel is
        #    on)
        # 3D: The height of the image (used to specify which row the pixel is
        #    on)
        # 4D: The RGB values of the pixel (used to specify which color value)
        #
        # For the y variables, they are 2 dimensional
        # 1D: The image (used to specify which image)
        # 2D: ??? This has something to do with the classification of the image
        #    ???
        print()
        print('x_train shape:', x_train.shape)
        print('x_test shape:', x_test.shape)
        print(x_train.shape[0], 'train samples')
        print(x_test.shape[0], 'test samples')
        print()
        print('y_train shape:', y_train.shape)
        print('y_test shape:', y_test.shape)
        print(y_train.shape[0], 'train samples')
        print(y_test.shape[0], 'test samples')

    # Convert class vectors to binary class matrices
    #
    # First Arg: The class vector to be converted to a matrix
    # Second Arg: The number of total classes
    # Third Arg: The data type that is returned by the call, default = float32
    y_train = keras.utils.to_categorical(y_train, NUM_OF_CLASSES)
    y_test = keras.utils.to_categorical(y_test, NUM_OF_CLASSES)

    if (DISPLAY_IMPORTANT_VARIABLES or DISPLAY_DEBUG_VARIABLES):
        # The shape of the numpy arrays
        #
        # The y variables are 2 dimnesional
        # 1D: The image (used to specify which image)
        # 2D: ??? See issue above ???
        print()
        print("After reshaping:")
        print('y_train shape:', y_train.shape)
        print('y_test shape:', y_test.shape)
        print(y_train.shape[0], 'train samples')
        print(y_test.shape[0], 'test samples')

    # Creating a sequential model
    #
    # A model is sequential because it is a linear stack of layers
    model = Sequential()

    # Adding a Conv2D layer
    #
    # Note: The first layer MUST specify the input shape. All other layers will
    #    assume this same shape if nothing is given
    #
    # input_shape: Requires a 4D tensor for the input shape (using the training
    #    input shape since that will be what goes into the layer as input)
    # padding: "same" means that the output will be the same length as the
    #    input. The default is "valid", which means no padding 
    # filters: This is the first number (the 32), and is the number of filters
    #    (the filters are used to extract features from the data)
    # kernel_size: The second argument here (the (3, 3)), and represents how
    #    wide the search range is when looking for a feature. So, in this case,
    #    when looking at a pixel, it will also gather everything in the pixels
    #    directly around the pixel it's looking at in order to gain more
    #    insight into what it's seeing
    model.add(Conv2D(32, (3, 3), padding='same', input_shape=x_train.shape[1:]))
    # activation: Putting this line here is the equivalent of passing
    #    "activation='relu'" as an argument in the previous line. This
    #    activation means that it will return 0 for any negative input, but for
    #    any positive input, it will return the largest value possible with x
    #    of the layer's function
    model.add(Activation('relu'))

    # Adding another layer. It's the same layer as above, except this time
    # there's no padding
    model.add(Conv2D(32, (3, 3)))
    model.add(Activation('relu'))

    # Adding another layer, a MaxPooling2D layer
    #
    # pool_size: The size of pool_size is how many pixels will be taken to form
    #    one pixel. The pixel that is chosen to stay is the pixel with the
    #    largest value (I think this number is gathered by the energy the pixel
    #    has?)
    model.add(MaxPooling2D(pool_size=(2, 2)))

    # Adding another layer, a Dropout layer
    #
    # rate: This is the 0.25, and specifies what chance (so, in this case,
    #    25%) the nueron has to drop out of the network when this layer is hit.
    #    It will select randomly every time. The goal of this is to train the
    #    network without having each nueron rely on its neighbors. If that
    #    happens, the network will become too focused on the training data and
    #    will have difficulty recognizing much outside of the training set
    model.add(Dropout(0.25))

    # Adding another layer
    #
    # This layer has already been explained above
    model.add(Conv2D(64, (3, 3), padding='same'))
    model.add(Activation('relu'))

    # Adding another layer
    #
    # This layer has already been explained above
    model.add(Conv2D(64, (3, 3)))
    model.add(Activation('relu'))

    # Adding another layer
    #
    # This layer has already been mostly explained above. The only difference
    # is that this layer does not specify the activation. The default
    # activation method is linear (so f(x) = x), and thus that is what this
    # layer's activation will be
    model.add(MaxPooling2D(pool_size=(2, 2)))

    # Adding another layer
    #
    # This layer has already been explained above
    model.add(Dropout(0.25))

    # Adding another layer
    #
    # A Flatten layer will take the input from a multidimensional array and
    # reshape it into a 1 dimensional array. I believe this helps the output
    # from getting too crazy and difficult for the nuerons to understand
    model.add(Flatten())

    # Adding another layer
    #
    # The dense layer will cause the output to be (num1, num2), where num1 is
    # the number given in the Dense layer (so in this case 512) and num2 is the
    # number of the input shape (so in this case refer to the first layer)
    model.add(Dense(512))
    model.add(Activation('relu'))

    # Adding another layer
    #
    # This layer has already been explained above
    model.add(Dropout(0.5))

    # Adding another layer
    #
    # This layer has already been explained above, except for the 'softmax'
    # activation. The softmax activation means that the layer will take all of
    # the input values and normalize it based on its probability distribution.
    # In this case, since the output will have 10 different options, the
    # softmax collects all of the input, normalizes it into the most likely
    # option for each image
    model.add(Dense(NUM_OF_CLASSES))
    model.add(Activation('softmax'))

    # Initiate the RMSprop Optimizer
    #
    # RMS Prop: I believe that this optimizer prohibits the movement along the
    #    y-axis, thus only allowing movement along the x-axis. This is useful
    #    so that converging on the lowest error rate possible is made easier
    #    since the y-value is gathered from the x-value, and not incremented as
    #    well
    # Learning Rate: The learning rate is the value at which the nueral network
    #    changes after every training (how much it adjusts itself to be
    #    better). It does this by attempting to move along the error rate to
    #    the point where the error rate is the lowest. A learning rate that's
    #    too large will cause it to become unstable while training, and thus
    #    come to inaccurate results. A learning rate too small means that the
    #    training process will take a long time and could potentially get stuck
    #    (due to a fluctuation of the error rate)
    # Decay: This is the amount the learning rate will decrease by after every
    #    training. This is so as the model becomes more accurate, it can move
    #    closer to the minimum on the error rate
    opt = keras.optimizers.RMSprop(learning_rate=0.0001, decay=1e-6)

    # Now it's time to compile the model
    #
    # Loss: This is how the model will determine the error rate. Different
    #    functions will result in yeilding different error rates for different
    #    values. For the selection of 'categorical_crossentropy', this means
    #    that the model will pick one from the category it's given. This is
    #    what we want since we are attempting to classify images
    # Optimizer: The optimizer the model will use. We created the optimizer in
    #    the previous line
    # Metrics: A metric is used to determine the performance of the model.
    #    Using 'accuracy' means that the model will be judged based on how
    #    accurate its guesses are (duh, lol). For example, if the first five
    #    images the model has classified as [0, 5, 3, 4, 4] and the correct
    #    classification for those images is [0, 5, 3, 3, 4], its accuracy will
    #    be 80% (4/5)
    model.compile(loss='categorical_crossentropy', optimizer=opt,
              metrics=['accuracy'])

    # Converting the data types to floats
    #
    # Why??? Thought they were already nums???
    x_train = x_train.astype('float32')
    x_test = x_test.astype('float32')

    # Dividing each value by 255
    #
    # We do this so that each pixel's value is ???
    x_train /= 255
    x_test /= 255

    # Not using data augmentation for the model
    if not USE_DATA_AUGMENTATION:
        # Training (fitting) the model
        model.fit(x_train, y_train, batch_size=BATCH_SIZE, epochs=EPOCHS,
              validation_data=(x_test, y_test), shuffle=True,
              callbacks=[tensorboard])
    # Using data augmentation for the model
    #
    # Using data augmentation is a great way to get increased diversity from
    # the dataset without increasing the size of the dataset. Data augmentation
    # is taking the given examples and rotating, flipping, or taking snippets
    # of them to be used as new examples
    else:
        # This will do preprocessing and realtime data augmentation
        datagen = ImageDataGenerator(
                featurewise_center=False,  # set input mean to 0 over the
                # dataset
                samplewise_center=False,  # set each sample mean to 0
                featurewise_std_normalization=False,  # divide inputs by std of
                # the dataset
                samplewise_std_normalization=False,  # divide each input by its
                # std
                zca_whitening=False,  # apply ZCA whitening
                zca_epsilon=1e-06,  # epsilon for ZCA whitening
                rotation_range=0,  # randomly rotate images in the range
                # (degrees, 0 to 180)
                # randomly shift images horizontally (fraction of total width)
                width_shift_range=0.1,
                # randomly shift images vertically (fraction of total height)
                height_shift_range=0.1,
                shear_range=0.,  # set range for random shear
                zoom_range=0.,  # set range for random zoom
                channel_shift_range=0.,  # set range for random channel shifts
                # set mode for filling points outside the input boundaries
                fill_mode='nearest',
                cval=0.,  # value used for fill_mode = "constant"
                horizontal_flip=True,  # randomly flip images
                vertical_flip=False,  # randomly flip images
                # set rescaling factor (applied before any other
                # transformation)
                rescale=None,
                # set function that will be applied on each input
                preprocessing_function=None,
                # image data format, either "channels_first" or "channels_last"
                data_format=None,
                # fraction of images reserved for validation (strictly between
                # 0 and 1)
                validation_split=0.0)

        # Compute quantities required for feature-wise normalization
        # (std, mean, and principal components if ZCA whitening is applied)
        datagen.fit(x_train)

        # Fit the model on the batches generated by datagen.flow()
        model.fit_generator(datagen.flow(x_train, y_train,
                batch_size=BATCH_SIZE), epochs=EPOCHS,
                validation_data=(x_test, y_test), workers=4,
                callbacks=[tensorboard])

    # Save model and weights
    #
    # This is checking to see if the directory exists or not. If it does NOT,
    # it creates that directory
    if not os.path.isdir(SAVE_DIRECTORY):
        os.makedirs(SAVE_DIRECTORY)
    # Creating the new model path with the specific model name and saving it
    model_path = os.path.join(SAVE_DIRECTORY, MODEL_NAME)
    model.save(model_path)
    
    # Letting the user know where the model is saved at and what it's name is
    print('Saved trained model at %s ' % model_path)

    # Score trained model
    scores = model.evaluate(x_test, y_test, verbose=1)
    print('Test loss:', scores[0])
    print('Test accuracy:', scores[1])

# This function runs many tests using the Keras Example
# WARNING: This function will take MANY HOURS, LIKELY a DAY or so
def performNumerousTests():
   # Performing a crap ton of tests
   #
   # Pattern of input:
   # performKerasExample(data_aug, batch, epoch, dir_name, mod_name)
   #
   # Any test that is commented out by a "#" is because these tests are likely
   # to cause Spyder to crash. Therefore, they are performed at the end of the
   # function in order of least likely to crash to most likely to crash
   
   # These tests all use data augmentation, a batch size of 32, but use
   # different epochs
   """performKerasExample(True, 32, 100, "test_1_32_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 32, 150, "test_2_32_Y_150\\", "cifar-10.h5")
   performKerasExample(True, 32, 200, "test_3_32_Y_200\\", "cifar-10.h5")
   performKerasExample(True, 32, 250, "test_4_32_Y_250\\", "cifar-10.h5")
   performKerasExample(True, 32, 300, "test_5_32_Y_300\\", "cifar-10.h5")
   
   # These tests all don't use data augmentation, a batch size of 32, but use
   # different epochs
   performKerasExample(False, 32, 100, "test_6_32_N_100\\", "cifar-10.h5")
   performKerasExample(False, 32, 150, "test_7_32_N_150\\", "cifar-10.h5")
   performKerasExample(False, 32, 200, "test_8_32_N_200\\", "cifar-10.h5")
   performKerasExample(False, 32, 250, "test_9_32_N_250\\", "cifar-10.h5")
   performKerasExample(False, 32, 300, "test_10_32_N_300\\", "cifar-10.h5")
   
   # These tests all use data augmentation, 100 epochs, but use different batch
   # sizes
   performKerasExample(True, 1, 100, "test_11_1_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 8, 100, "test_12_8_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 16, 100, "test_13_16_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 32, 100, "test_14_32_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 64, 100, "test_15_64_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 128, 100, "test_16_128_Y_100\\", "cifar-10.h5")
   #performKerasExample(True, 10000, 100, "test_17_10000_Y_100\\", "cifar-10.h5")
   #performKerasExample(True, 50000, 100, "test_18_50000_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 256, 100, "test_19_256_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 512, 100, "test_20_512_Y_100\\", "cifar-10.h5")
   #performKerasExample(True, 1024, 100, "test_21_1024_Y_100\\", "cifar-10.h5")
   
   # These are starting to figure out the optimal solution tests from data
   # gathered
   performKerasExample(False, 128, 110, "test_22_128_N_110\\", "cifar-10.h5")"""
   performKerasExample(False, 128, 120, "test_32_128_N_120\\", "cifar-10.h5")
   """performKerasExample(True, 128, 110, "test_23_128_Y_110\\", "cifar-10.h5")
   #performKerasExample(False, 256, 110, "test_24_256_N_110\\", "cifar-10.h5")
   performKerasExample(False, 64, 110, "test_25_64_N_110\\", "cifar-10.h5")
   performKerasExample(False, 64, 120, "test_26_64_N_120\\", "cifar-10.h5")
   
   # These tests are also run on my model to compare
   performMyExample(False, 128, 110, "test_27_128_N_110_MyModel\\", "cifar-10.h5")"""
   performKerasExample(False, 128, 120, "test_33_128_N_120\\", "cifar-10.h5")
   """performMyExample(True, 128, 110, "test_28_128_Y_110_MyModel\\", "cifar-10.h5")
   performMyExample(False, 64, 110, "test_29_64_N_110_MyModel\\", "cifar-10.h5")
   performMyExample(False, 64, 120, "test_30_64_N_120_MyModel\\", "cifar-10.h5")
   performMyExample(False, 256, 110, "test_31_256_N_110_MyModel\\", "cifar-10.h5")"""
   # NEXT MODEL IS  NOT TEST #32, BUT TEST #34 (see between tests 22 and 23 and tests 27 and 28)
   
   # Tests that are (somewhat) likely to crash Spyder
   """performKerasExample(False, 256, 110, "test_24_256_N_110\\", "cifar-10.h5")
   performKerasExample(True, 1024, 100, "test_21_1024_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 10000, 100, "test_17_10000_Y_100\\", "cifar-10.h5")
   performKerasExample(True, 50000, 100, "test_18_50000_Y_100\\", "cifar-10.h5")"""

# This function is the optimal solution that I have found for the CIFAS-10
# dataset
def performOptimalSolution():
    print("Perform optimal solution")

# This function gets the menu input and calls the appropriate functions
def menu():
    # Creating the menu string
    menuString = "Menu:\n"
    menuString += "1. Perform Keras 2010 Baseline test\n"
    menuString += "2. Perform my optimal solution to the CIFAS-10 data set\n"
    menuString += "3. Perform many tests (31)\n"
    menuString += "4. Perform every option\n"
    menuString += "5. Quit\n"
    menuString += "Enter your selection here: "
    
    # Creating the warning string in case the user chooses 3 or 4
    warningString = "WARNING! The amout of tests that will be performed will "
    warningString += "take anywhere from several days to a week to complete! "
    warningString += "Are you sure you would like to continue?\n"
    warningString += "1. Yes\n"
    warningString += "2. No\n"
    warningString += "Enter your selection here: "
    
    # Default setting for userChoice to make sure the loop is entered
    userChoice = 1
    
    while(userChoice != 5):
        # Getting the user's input
        userChoice = getNumInRange(1, 5, menuString)
    
        # Performing the user's choice
        if (userChoice == 1):
            performBaselineKerasTest()
        elif (userChoice == 2):
            performOptimalSolution()
        elif (userChoice == 3):
            # Making sure the user actually wants to do this
            userChoice = getNumInRange(1, 2, warningString)
            if (userChoice == 1):
                performNumerousTests()
        elif (userChoice == 4):
            # Making sure the user actually wants to do this
            userChoice = getNumInRange(1, 2, warningString)
            if (userChoice == 1):
                performBaselineKerasTest()
                performOptimalSolution()
                performNumerousTests()

#
#
# Main
#
#

# If I do NOT want to show debug variables (or messages, in this case)
if (not DISPLAY_DEBUG_VARIABLES):
    # Turning off all warnings from tensorflow
    tf.compat.v1.logging.set_verbosity(tf.compat.v1.logging.ERROR)

# See what the user wants to do
menu()
















