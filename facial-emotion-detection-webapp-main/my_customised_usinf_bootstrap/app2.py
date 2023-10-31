from flask import Flask, render_template, request, Response
import cv2
import numpy as np 
from tensorflow.keras.models import load_model
from keras_preprocessing.image import img_to_array

app = Flask(__name__)

app.config['SEND_FILE_MAX_AGE_DEFAULT'] = 1
camera = cv2.VideoCapture(0)
face_classifier = cv2.CascadeClassifier(r'G:\3.2\system project\Emotion_Detection_CNN-main\haarcascade_frontalface_default.xml')
label_map = ["ANGRY", "DISGUST","FEAR","HAPPY", "NEUTRAL","SAD","SURPRISED"]
classifier =load_model('model.h5')
def gen_frames():
    while True:
        success, frame = camera.read()
        if not success:
            break
        else:
            frame = camera.read()
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
                    label=label_map[prediction.argmax()]
                    label_position = (x,y)
                    cv2.putText(frame,label,label_position,cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0),2)
                else:
                    cv2.putText(frame,'No Faces',(30,80),cv2.FONT_HERSHEY_SIMPLEX,1,(0,255,0),2)
            cv2.imshow('Emotion Detector',frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break       
@app.route('/')
def index():
    return render_template('index2.html')
@app.route('/')
def video_feed():
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')



if __name__ == "__main__":
	app.run(debug=True)