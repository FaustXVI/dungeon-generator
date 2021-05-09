type peril = Creature | SimpleDanger | ComplexDanger

type encounter = { perils :  list (peril) }

let generateEncounter= () => { perils : [Creature,Creature] }




