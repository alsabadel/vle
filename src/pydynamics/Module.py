import testDynamics

class MyModel(testDynamics.Dynamics):
    
    def output(self,time,events):
        #MySet = testDynamics.Set()
	MyMap = testDynamics.Map.create()
        MySet = testDynamics.Set.create()
        MyDouble = self.buildDouble(2.0)
        MyInteger = self.buildInteger(1)
        MyBoolean = self.buildBoolean(True)
        MyString = self.buildString("String")
        print "********************************************"
	print "Type de MyMap :", type(MyMap)
        print "Type de MyDouble :", type(MyDouble)
        print "********************************************"
        MyMap.addBoolean("Bool1", MyBoolean)
        print "MyMap Boolean 1 :", MyMap.getBoolean("Bool1")
        MyMap.addBoolean("Bool2", False)
        print "MyMap Boolean 2 :", MyMap.getBoolean("Bool2")

        MyMap.addDouble("Double", 2.0)
        print "MyMap Double :",MyMap.getDouble("Double")
        MyMap.addInt("Int", 1)
        print "MyMap Integer :",MyMap.getInt("Int")
        MyMap.addString("Str", "value")
        print "MyMap String :",testDynamics.toString(MyMap.get("Str")) 
        MyMap.addMap("Map")
        print "MyMap Map :",MyMap.getMap("Map")
        MyMap.addSet("Set")
        #print "MyMap Set :",MyMap.getSet("Set")

        #print type(MyInteger)	       
        #print dir(testDynamics)	
        #print "********************************************"
        #print "Test des Value (Double,String,Integer,Boolean)"
        #test = MyDouble.isDouble()
        #print "MyDouble est un double :",test
        #test = MyDouble.isInteger()
        #print "MyDouble est un integer :",test
        #test = MyInteger.isInteger()
        #print "MyInteger est un integer :",test
        #test = MyBoolean.isBoolean()
        #print "MyBoolean est un boolean :",test
        #test = MyString.isString()
        #print "MyString est un string :",test
        print "********************************************"
        print "Creation des evenements"
        eventA= self.buildEvent("PortA")
        eventB= self.buildEventWithAInteger("PortB", "NomAttributB", 1) 
        eventC= self.buildEventWithADouble("PortC", "NomAttributC", 2.2)
        eventD= self.buildEventWithABoolean("PortD", "NomAttributD", False)  
        eventE= self.buildEventWithAString("PortE", "NomAttributE", "value") 
        #print "********************************************"

        #print "Ajout des evenements a la liste d'evenements"
	#events.append(eventA);
        #events.append(eventB);   
	#events.append(eventC); 
	#events.append(eventD); 
	#events.append(eventE);    
	

    def init(self, time): 
        if time == 0.0:
            return 1.0
        else :
            return testDynamics.infinity

    def testBoolean(self):
        print "********************************************"
        print "***Test de Boolean.hpp***"
	print "Creation d'un boolean avec create(False)"        
        MyBoolCreate = testDynamics.Boolean.create(False)
	print "Creation d'un boolean avec Boolean()" 
        MyBoolean1 = testDynamics.Boolean()
	print "Creation d'un boolean avec Boolean(True)" 
        MyBoolean2 = testDynamics.Boolean(True)
	print "Clone de MyBoolean2" 
        MyBooleanClone = MyBoolean2.clone()
	print "MyBoolean1.set(False)"		
        MyBoolean1.set(False)
        print "********"
	print "MyBoolan1 est de type :", MyBoolean1.getType()
	print "MyBoolan2 est de type :", MyBoolean2.getType()
	print "MyBoolCreate est de type :", MyBoolCreate.getType()
	print "MyBooleanClone est de type :", MyBooleanClone.getType()
	print "********"
        print "MyBoolan1 a pour valeur :", MyBoolean1.value()
        print "MyBoolan2 a pour valeur :", MyBoolean2.value()	
	print "MyBoolCreate a pour valeur :", MyBoolCreate.value()

    def testDouble(self):
        print "********************************************"
        print "***Test de Double.hpp***"
	print "Creation d'un double avec create(3.0)" 
        MyDoubleCreate = testDynamics.Double.create(3.0)
	print "Creation d'un double avec Double()"
        MyDouble1 = testDynamics.Double()
	print "Creation d'un boolean avec Double(2.0)" 
        MyDouble2 = testDynamics.Double(2.0)
	print "Clone de MyDouble2" 
        MyDoubleClone = MyDouble2.clone()
	print "MyDouble1.set(1.0)"	
        MyDouble1.set(1.0)
	print "********"
	print "MyDouble1 est de type :", MyDouble1.getType()
	print "MyDouble2 est de type :", MyDouble2.getType()
	print "MyDoubleCreate est de type :", MyDoubleCreate.getType()
	print "MyDoubleClone est de type :", MyDoubleClone.getType()
	print "********"
	print "MyDouble1 a pour valeur :", MyDouble1.value()       
	print "MyDouble2 a pour valeur :", MyDouble2.value()  
	print "MyDoubleCreate a pour valeur :", MyDoubleCreate.value()  

    def testInteger(self):
        print "********************************************"
        print "***Test de Integer.hpp***"
	print "Creation d'un integer avec create(3)" 
        MyIntegerCreate = testDynamics.Integer.create(3)
	print "Creation d'un integer avec Integer()"
        MyInteger1 = testDynamics.Integer()
	print "Creation d'un integer avec Integer(2)" 
        MyInteger2 = testDynamics.Integer(2)
	print "Clone de MyInteger2" 
        MyIntegerClone = MyInteger2.clone()
	print "MyInteger1.set(1)"	
        MyInteger1.set(1)
	print "********"
	print "MyInteger1 est de type :", MyInteger1.getType()
	print "MyInteger2 est de type :", MyInteger2.getType()
	print "MyIntegerCreate est de type :", MyIntegerCreate.getType()
	print "MyIntegerClone est de type :", MyIntegerClone.getType()
	print "********"
	print "MyInteger1 a pour valeur :", MyInteger1.value()       
	print "MyInteger2 a pour valeur :", MyInteger2.value()  
	print "MyIntegerCreate a pour valeur :", MyIntegerCreate.value()  

    def testString(self):
        print "********************************************"
        print "***Test de String.hpp***"
	print "Creation d'un string avec create(Trois)" 
        MyStringCreate = testDynamics.String.create("Trois")
	print "Creation d'un string avec String()"
        MyString1 = testDynamics.String()
	print "Creation d'un string avec String(Deux)" 
        MyString2 = testDynamics.String("Deux")
	print "Clone de MyString2" 
        MyStringClone = MyString2.clone()
	print "MyString1.set(Un)"	
        MyString1.set("Un")
	print "********"
	print "MyString1 est de type :", MyString1.getType()
	print "MyString2 est de type :", MyString2.getType()
	print "MyStringCreate est de type :", MyStringCreate.getType()
	print "MyStringClone est de type :", MyStringClone.getType()
	print "********"
	print "MyString1 a pour valeur :", MyString1.value()       
	print "MyString2 a pour valeur :", MyString2.value()  
	print "MyStringCreate a pour valeur :", MyStringCreate.value() 

    def testMap(self):
        print "********************************************"
        print "***Test de Map.hpp***"
	print "Creation d'un Map avec create()" 
        MyMapCreate = testDynamics.Map.create()
	print "Creation d'un Map avec Map()"
        MyMap1 = testDynamics.Map()
	print "Creation d'un string avec Map(Deux)" 
        MyString2 = testDynamics.String("Deux")
	print "Clone de MyString2" 
        MyStringClone = MyString2.clone()
	print "MyString1.set(Un)"	
        MyString1.set("Un")
	print "********"
	print "MyString1 est de type :", MyString1.getType()
	print "MyString2 est de type :", MyString2.getType()
	print "MyStringCreate est de type :", MyStringCreate.getType()
	print "MyStringClone est de type :", MyStringClone.getType()
	print "********"
	print "MyString1 a pour valeur :", MyString1.value()       
	print "MyString2 a pour valeur :", MyString2.value()  
	print "MyStringCreate a pour valeur :", MyStringCreate.value() 

    def ExternalEvent(self):
        print "********************************************"
        print "***Test de ExternalEvent.hpp***" 
	print "Creation d'un ExternalEvent avec ExternalEvent(MonPort)" 
        MyEvent = testDynamics.ExternalEvent("MonPort") 
	print "MyEvent est sur le port :", MyEvent.getPortName ()
	print "MyEvent est sur le port MonPort ? :", MyEvent.onPort ("MonPort")
	print "Creation d'un Map avec Map()"
        MyMap = testDynamics.Map()
        print "Ajout d'un Map a l'ExternalEvent" 
        print dir(MyEvent)
        #MyEvent.putAttributes(MyMap)

    def externalTransition(self, time, events):
        print "********************************************"
        print "Test des noms de port"
        print "Le nom du Port de eventA :",events[0].getPortName()
        print "Le nom du Port de eventB :",events[1].getPortName()
        print "Le nom du Port de eventC :",events[2].getPortName()
        print "Le nom du Port de eventD :",events[3].getPortName()
        print "Le nom du Port de eventE :",events[4].getPortName()
        print "********************************************"
        print "Test la presence d'un attribut"
        print "Presence d'un attribut pour eventA :",events[0].haveAttributes()
        print "Presence d'un attribut pour eventB :",events[1].haveAttributes()
        print "********************************************"
        print "Affichage de l'attribut"
        print "Attribut pour eventB :",events[1].getIntegerAttributeValue("NomAttributB")
        print "Attribut pour eventC :",events[2].getDoubleAttributeValue("NomAttributC")
        print "Attribut pour eventD :",events[3].getBooleanAttributeValue("NomAttributD")
        print "Attribut pour eventE :",events[4].getStringAttributeValue("NomAttributE")

print "Initialisation du Modele..."
modelinit = testDynamics.DynamicsInit()
a = MyModel(modelinit)
print "Creation de la liste d'evenements..."
lst = testDynamics.ExternalEventList()
assert(a.init(0.0) == 1.0)
a.output(0.0, lst)
#Test de Boolean.hpp
#a.testBoolean()
#Test de Double.hpp
a.testDouble()
#Test de Integer.hpp
#a.testInteger()
#Test de String.hpp
a.testString()
#Test de ExternalEvent.hpp
#a.ExternalEvent()
#a.externalTransition(0.0,lst)
#print dir(eventB)
#print type(events)
