import jmri
class setStartup(jmri.jmrit.automat.AbstractAutomaton) :
   def init(self):
      return
   
   def handle(self):
      turnouts.provideTurnout("CT2").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT3").setState(CLOSED)
      self.waitMsec(1000)         # time is in milliseconds
      turnouts.provideTurnout("CT4").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT5").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT6").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT7").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT8").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT9").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT10").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT11").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT12").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT13").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT14").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT15").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT16").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT17").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT18").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT19").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT21").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT22").setState(CLOSED)
      self.waitMsec(1000)
      turnouts.provideTurnout("CT23").setState(CLOSED)

      return false              # all done, don't repeat again

setStartup().start()          # create one of these, and start it running 
