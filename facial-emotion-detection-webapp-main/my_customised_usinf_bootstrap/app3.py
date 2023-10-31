from flask import Flask, render_template, Response
import cv2
from keras.models import load_model
from time import sleep
from keras_preprocessing.image import img_to_array
from keras.preprocessing import image
import numpy as np

app=Flask(__name__)

face_classifier = cv2.CascadeClassifier('haarcascade_frontalface_alt2.xml')
classifier =load_model(r'G:\3.2\system project\Emotion_Detection_CNN-main\model.h5')

emotion_labels = ['Angry','Disgust','Fear','Happy','Neutral', 'Sad', 'Surprise']

camera = cv2.VideoCapture(0)

def generate_frame():
    while True:
        success,frame=camera.read()
        if not success:
            break
        else:
            labels = []
            gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
            faces = face_classifier.detectMultiScale(gray)

            for (x,y,w,h) in faces:
                cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,255),2)
                roi_gray = gray[y:y+h,x:x+w]
                roi_gray = cv2.resize(roi_gray,(48,48),interpolation=cv2.INTER_AREA)



                if np.sum([roi_gray])!=0:
                    roi = roi_gray.astype('float')/255.0
                    roi = img_to_array(roi)
                    roi = np.expand_dims(roi,axis=0)

                    prediction = classifier.predict(roi)[0]
                    label=emotion_labels[prediction.argmax()]
                    label_position = (x,y)
                    cv2.putText(frame,label,label_position,cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0),2)
                else:
                    cv2.putText(frame,'No Faces',(30,80),cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0),2)
            cv2.imshow('Emotion Detector',frame)
            ret,buffer=cv2.imencode('.jpg',frame)
            frame=buffer.tobytes()
        yield(b'--frame\r\n'
                    b'content-type:image/jprg\r\n\r\n'+frame+b'\r\n')

@app.route('/')
def index():
    return render_template('index3.html')
@app.route('/video')
def video():
    return Response(generate_frame(),mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == "__main__":
    app.run(debug=True)
