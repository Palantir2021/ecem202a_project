# Project Proposal

## 1. Motivation & Objective

More than 80% of information that human brain processes is visual. Therefore, visually impaired people face a great challenge of sensing the outside world, especially when they need to move through an unknown environment. The goal of this project is to build an low-cost, robust and user-friendly obstacle avoidance system, with Arduino Nano 33 BLE Sense, Raspberry Pi 3, Ultrasound module, IR camera, eSense earable compute platform, aid of a smartphone and other minor parts, to detect and warn obstacles for the visually impaired users, which improves their outdoor mobility, and quality of life.

## 2. State of the Art & Its Limitations

The most useful assistance for visually impaired people has been the guide dogs, which need to be trained at a high cost to navigate blind people through obstacles, and have physical needs to be taken care of. And in China, there are tens of millions of blind people with a total of two hundred guide dogs bred in ten years, and now less than one hundred are in service. Those who cannot afford a guide dog usually employ a white cane, which can only detect obstacles near to the ground.    
With the development of electronics industry, a wide range of devices were invented to aid visually impaired people in their indoor and outdoor activities. Earliest inventions employ cheap ultrasonic and sonar sensors, which are still welcomed in today's designs, and lasers to detect the distance of obstacles. However, due to the difficulties in calibration, manual scanning and reflective error exclusion[1], those sensors are mostly used alongside more accurate detectors as auxiliary equipment.    
Modern obstacle avoidance systems are embedded into wearable or portable devices. Examples of the former are Eyeronman[2] smart vest that uses vibration to translate sensor data to tactile information, and Project Guideline[3] belt that uses camera to sense and sound tone to provide feedback. The latter is mostly realized in the form of smart canes, including Augmented Cane [4] which employs a comprehensive set of modules including LIDAR, camera, GPS and IMU, whose data can be feedback to user with grounded kinesthetic omni-wheel, audio and push button, and WeWalk[5] which has ultrasonic above-ground obstacle detection, automatic voice feedback and smartphone application-aided navigation and transportation assistant.    
The most obvious limitation of modern devices is high cost, mainly due to the employment of complicated sensors and high-standard algorithms. Also, a smart cane need to be held at all time, which limits the hand mobility of its user.    

## 3. Novelty & Rationale

Our obstacle detection system utilizes relatively simple sensors (IR camera, ultrasonic sensors, Earable gyroscope) and control units (Arduino Nano 33 BLE Sense, Raspberry Pi) to achieve high accuracy and wide range  of obstacle detection, with fast, user-friendly voice feedback (Earable earphones). Current structure is: the IR camera, which is placed on the head of user, detects a wide range of obstacles, whose data is sent and processed by Raspberry Pi (RBPi), who classifies the obstacles and judges if any obstacle is too near and its distance to the user needs to be further measured. RBPi then sends data back to the controlling Arduino Nano 33 BLE Sense (Arduino). If the obstacles are near enough to the user, the ultrasonic sensors will measure the exact distance, and send data to its Arduino to be processed and then sent to the controlling Arduino. If there is indeed an obstacle that needs to be avoided, the controlling Arduino will communicate with Earable smartphone application via Bluetooth, which then communicates with Earable earphone to vocally remind the user of the obstacle.

## 4. Potential Impact

We intend to make a prototype of low-cost, high-accuracy obstacle detecting and warning system.  It will provide a new possibility of the choice and combination of sensors, controllers and smart phone applications, and a new way of user-device interaction to the industry of obstacle avoidance for visually impaired people. It allows blind people to improve their outdoor safe mobility, therefore quality of life, with relatively low cost.

## 5. Challenges

The first challenge of this project is the accuracy of ultrasonic sensors, which, being a cheap module, can sometimes be inaccurate due to reflection, and thus need to be calibrated with algorithms. The second challenge is to maintain the robustness of the system, for it has many components, especially camera recognition will take up a lot of computing time. All these parts need to work in accordance, being able to tolerate perturbations and interruptions.


## 6. Requirements for Success

- The task can be divided into the following three parts:    
    - Arduino & Ultrasound    
    - Raspberry Pi & IR camera    
    - Earable & App development    
- The resources needed for this projects are listed below:    
    - Devices：    
        1. Arduino Nano 33 BLE Sense    
        2. Raspberry Pi 3    
        3. IR camera    
        4. Ultrasonic sensors    
        5. Earable earphones     
        6. Smartphone    
        7. Other auxiliary parts     
    - Software:    
        1. Arduino IDE   
        2. Android studio   
        3. Earable smartphone application   
    - Background research materials:    
        1. Various IEEE papers    
        2. Arduino and Raspberry Pi tutorials      
- The skills needed are:    
    - Arduino and Raspberry Pi programming
    - Use of neural networks ‘YOLO’
    - Android application development (Java)    
    - GitHub    
    - Hardware usage, connection and debugging    
    - Teamworking     
    - Time management    

## 7. Metrics of Success

A successful obstacle detecting and warning system must have the following properties: fast and accurate obstacle detecting, proper classification and judgement of obstacles, in-time and clear warning, easy operation and robustness. They can be qualified as:     
    - The speed with which the system response to obstacle (in seconds)     
    - The rate of successful obstacle detection (%), while the obstacles' type, distance, moving speed vary     
    - The speed with which a user walks under the assistance of our system    
    To measure those metrics, various tests and trials can be conducted.    

## 8. Execution Plan

1. Obstacle detection and reminder     
2. Obstacle pre-recognition by camera    
3. Development of Earable application on Arduino smart phone    
4. Programming the controller Arduino and communication between parts  
Partitioning:      
Task 1 is to be done by Ruoye Wang, task 2,3 are to be done by Jinchen Wu, and task 4 is done together.   

## 9. Related Work

### 9.a. Papers

Many modern designs still use the shape of a white cane, only that the white cane now has senses.       
The Augmented Cane, presented by Slade et al. [4], utilizes multiple kinds of sensors including 2D LIDAR, camera, GPS antenna, and inertial measurement unit to provide various functions like obstacle avoidance, orientation and navigation. It shows a wide range of choice of sensors and feedbacks. However, most of its sensors are expensive and overqualified for our goal.      
With lower cost, Wahab et al. [6] produce a prototype of smart cane that detects obstacles with 40kHz ultrasonic sensors, and feeds warning back in the form of voices, only 3 types of which are provided. Chung et al. [7] present another design of smart cane that utilizes an ultrasonic sensor to detect obstacles and a gyroscope to prevent falling; it also has a voice navigation system which communicates with smartphone application via Bluetooth to guide the user to their destination.      
The above realization of smart canes have proven the feasibility of ultrasonic obstacle detection, and the latter, in particular, enlightened us that smart phone applications can be connected to the device via Bluetooth to provide more user-friendly feedback.       
Additionally, We need to use the camera for more real-time obstacle detection, so we will refer to the smaller and faster YOLOv5s[8] to implement this function, and optimize it for our usage scenarios. We also infer the article Earables for Personal-Scale Behavior Analytics[9], which introduces a programmable earphone with sensors such as a built-in gyroscope. We use this earable to provide obstacle detection feedback, and the built-in sensor data can also provide corrections to the obstacle detection algorithm. This article and related technical documents help us develop a mobile application adapted to our project.   


### 9.b. Datasets

We will use COCO[10] and VOC[11] to finetune our 'YOLO' network.    

### 9.c. Software

List softwate that you have identified and plan to use. Provide references (with full citation in the References section below).
- Android studio    
- Arduino IDE    


## 10. References

[1] Hossain, E., Khan, M.R., Muhida, R. and Ali, A. (2011) ‘State of the art review on walking support system for visually impaired people’, Int. J. Biomechatronics and Biomedical Robotics, Vol. 1, No. 4, pp.232–251     
[2] https://tactilenavigationtools.com/#:~:text=The%20Eyeronman%2C%20is%20a%20hands,user's%20through%20superior%20situation%20awareness    
[3] Project Guideline: Can Technology Help A Blind Runner Navigate     
[4] P. Slade, A. Tambe, M. J. Kochenderfer, Multimodal sensing and intuitive steering assistance improve navigation and mobility for people with impaired vision. Sci. Robot. 6, eabg6594 (2021)    
[5] https://wewalk.io/en/    
[6] M. Wahab, A. Talib, H. Kadir, A. Johari, A. Noraziah, R. Sidek and A. Mutalib, "Smart Cane: Assisitive Cane for Visually-impaired People", International Journal of Computer Science Issues, Vol. 8, Issue 4, No 2, pp. 21-27, July 2011       
[7] I. Chung, S. Kim and K. Rhee, "The Smart Cane Utiliziing a Smart Phone for the VIsually Impaird Person," in IEEE 3rd Glob. Conf. Consum. Electron.(GCCE), 2014, pp. 106-107        
[8] Fahim Kawsar, Chulhong Min, Akhil Mathur, Alessandro Montanari, Utku Gunay Acer, Marc Van den Broeck, Nokia Bell Labs, ESense: Open Earable Platform for Human Sensing, ACM MobiSys 2018, ACM UbiComp 2018, ACM SenSys 2018       
[9] https://docs.ultralytics.com/      
[10] https://cocodataset.org/#home     
[11] https://www.tensorflow.org/datasets/catalog/voc     



