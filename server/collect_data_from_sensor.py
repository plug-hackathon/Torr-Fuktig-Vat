
import socket
import datetime

class Sensor:


    # dict thats converted to json when returned
    data = {
        'temperature': 0.0,
        'date': '',
        'time': '',
        'name': '',
    }

    # This part reads from the port
    def read(self):

        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(('', 16000))

        try:
            data, sockname = sock.recvfrom(25)
            data = data.decode('utf-8')

            name_and_temp_array = str(data).split(';')
            #print(name_and_temp_array)
            #print(name_and_temp_array[0])
            #print(name_and_temp_array[1][:-3])
            self.data['name'] = name_and_temp_array[1] # Name
            self.data['temperature'] = float(name_and_temp_array[0]) # Temperature
            self.data['time'] = datetime.datetime.now().strftime("%H:%M:%S") # Time
            self.data['date'] = datetime.datetime.now().strftime("%y%m%d") # Date


            sock.close()
            return self.data

        except IndexError as e:
            print(data)
            print(e)
            #time.sleep(10)
            sock.close()
        except TypeError as e:
            print(data)
            print(e)
            #time.sleep(10)
            sock.close()
        except ValueError as e:
            print(data)
            print(e)
            #time.sleep(10)
            sock.close()

def test():

    port = 16000
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(("", port))
    print "waiting on port:", port
    while 1:
        data, addr = s.recvfrom(25)
        print data

if __name__ == '__main__':
    a = Sensor()
    while True:
        print(a.read())
