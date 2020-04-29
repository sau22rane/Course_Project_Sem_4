from random import randint
cities =[ "Mumbai","Delhi","Bangalore","Hyderabad","Ahmedabad","Chennai","Kolkata","Surat","Pune","Jaipur","Kanpur","Nagpur","Lucknow","Visakhapatnam","Thane","Bhopal","Indore","Pimpri-Chinchwad","Patna","Vadodara","Ghaziabad","Ludhiana","Agra","Nashik","Faridabad","Meerut","Rajkot","Kalyan-Dombivli","Vasai-Virar","Varanasi"]
companies = ["IndiGo","Air India","SpiceJet","GoAir","AirAsia India","Vistara","Alliance Air","Air India Express","TruJet","Qatar Airways","Saudi Airlines Saudia","Etihad Airways"]
l=[]
for i in range(50,801,50):
    while(len(l)<i):
        a = randint(1000+i-50,1000+i)
        if a not in l:
            l.append(a)
f = open("flight data.csv","w")
for i in range(len(l)):
    f.write(str(l[i])+","+companies[randint(0,len(companies)-1)].upper()+","+cities[randint(0,len(cities)-1)].upper()+","+cities[randint(0,len(cities)-1)].upper()+","+str(randint(1,30))+"/"+str(randint(5,7))+"/"+str(2020)+","+str(randint(0,23))+":"+str(randint(0,59))+","+str(randint(4000,10000))+"\n")


f.close()