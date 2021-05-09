open Belt.List;

type peril = Creature | SimpleDanger | ComplexDanger

type encounter = { perils :  list (peril) }

let generateEncounter= (~perils: array(peril)) => { perils : [perils[0], perils[0]] }

let experiencePoints= (~encounter : encounter) => 40 * length(encounter.perils)

