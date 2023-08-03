from pyrebase import pyrebase
from pusher_push_notifications import PushNotifications

firebaseConfig = {} #config file can be downloaded from your firebase web dashboard

firebase = pyrebase.initialize_app(firebaseConfig)

db = firebase.database()

instanceid = "your_pusherbeams_instanceid"
secretkey = "your_pusherbeams_secretkey"

beams_client = PushNotifications(
    instance_id=instanceid,
    secret_key=secretkey
)

def stream_handler(message):
    value = message["data"]
    if(message["event"] == "put"):
      updatedval = message["data"]
      try :
        print(updatedval)
        #tag = updatedval["tag"]
        #time = updatedval["time"]
        #usertype = updatedval["usertype"]
        #print("Usertype : "+usertype, "Tag: "+tag, "Time: "+time)
        print(type(updatedval))
        if(updatedval == "INVALID USER"):
          response = beams_client.publish_to_interests(
          interests=['hello'],
          publish_body={
            'apns': {
              'aps': {
                'alert': {
                  'title': 'An Invalid User!',
                  'body': 'An Invalid User has accessed your device, check now!!',
                },
              },
            },
            'fcm': {
              'notification': {
                'title': 'An Invalid User!',
                'body': 'An Invalid User has accessed your device, check now!!',
              },
              'android': {
                'priority':'high'
              }
            },
            'web': {
              'notification': {
                'title': 'An Invalid User!',
                'body': 'An Invalid User has accessed your device, check now!!',
              },
            },
          },)
          print(response['publishId'])
        elif(updatedval == "MANAGER"):
          response = beams_client.publish_to_interests(
          interests=['hello'],
          publish_body={
            'apns': {
              'aps': {
                'alert': {
                  'title': 'A manager has accessed the device.',
                  'body': 'Click here to see the Logs.',
                },
              },
            },
            'fcm': {
              'notification': {
                'title': 'A manager has accessed the device.',
                'body': 'Click here to see the Logs.',
              },
            },
            'web': {
              'notification': {
                'title': 'A manager has accessed the device.',
                'body': 'Click here to see the Logs.',
              },
            },
          },)
          print(response['publishId'])
        elif(updatedval=="EMPLOYEE"):
          response = beams_client.publish_to_interests(
          interests=['hello'],
          publish_body={
            'apns': {
              'aps': {
                'alert': {
                  'title': 'An employee has accessed the device.',
                  'body': 'Click here to see the logs.',
                },
              },
            },
            'fcm': {
              'notification': {
                'title': 'An employee has acessed the device.',
                'body': 'Click here to see the logs.',
              },
            },
            'web': {
              'notification': {
                'title': 'An employee has accessed the device.',
                'body': 'Click here to see the logs.',
              },
            },
          },)
          print(response['publishId'])
      except KeyError:
        pass

my_stream = db.child("Users").stream(stream_handler)