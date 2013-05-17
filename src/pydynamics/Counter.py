import testDynamics

class Counter(testDynamics.Dynamics):
    def __init(self):
        self.counter = 0
        self.active = False

    def __init__(self, model): 
        testDynamics.Dynamics.__init__(self, model)
        self.counter = 0
        self.active = False
    
    def output(self, time, output):
        output.addEvent(self.buildEvent("out"))

    def timeAdvance(self):
        if self.active:
	    return testDynamics.Time(1)
        else:
            return testDynamics.infinity

    def init(self, time): 
        counter = 0
        active = False
        return testDynamics.infinity
    
    def internalTransition(self, time):
        self.active = False;

    def externalTransition(self, eventlist, time):
        self.counter += 1
        self.active = True

    def observation(self, event):
        if event.onPort("c"):
            return self.buildDouble(self.counter)
        else:
            return None

modelinit = testDynamics.DynamicsInit()
a = Counter(modelinit)
a.timeAdvance()
lst = testDynamics.ExternalEventList();
#a.output(0.0, lst)
a.internalTransition(1.0)
a.externalTransition(lst, 1.0)


