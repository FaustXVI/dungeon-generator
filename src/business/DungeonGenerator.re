open Belt.List;


type peril = Creature | SimpleDanger | ComplexDanger

type encounter = { perils :  list (peril) }

let pickRandom = Belt.List.head
let generateEncounter= (~perils: array(peril),~choose: list(peril) => option(peril) = pickRandom, ()) => {
    let element = choose([perils[0]]);
    switch(element) {
        | None => { perils : [] }
        | Some(e) => { perils : [e,e] }
    }
}

let experiencePoints= (~encounter : encounter) => 40 * length(encounter.perils)

