import jmri
class setStartup(jmri.jmrit.automat.AbstractAutomaton) :
   def init(self):
     return
   def handle(self):
     self.waitMsec(10000)         # time is in milliseconds
     turnouts.provideTurnout("4").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("5").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("6").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("7").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("8").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("9").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("10").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("11").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("12").setState(CLOSED)
     self.waitMsec(1000)
     turnouts.provideTurnout("13").setState(CLOSED)
     return False              # all done, don't repeat again
setStartup().start()          # create one of these, and start it running 
