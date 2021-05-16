open Belt.List;


type peril = Creature | SimpleDanger

type encounter = { perils :  list (peril) }

type chooser = list(peril) => option(peril)

let pickRandom = Belt.List.head

let generateEncounter= (~perils: array(peril),~chooser: chooser = pickRandom, ()) => {
    if (Array.length(perils) == 2) {
        let element = chooser([SimpleDanger]);
        switch(element) {
            | None => { perils : [] }
            | Some(encounter) => { perils : map([1,2,3,4,5,6,7,8,9,10], _ => encounter) }
        }
    } else {
        let element = chooser([Creature]);
        switch(element) {
            | None => { perils : [] }
            | Some(encounter) => { perils : map([1,2], _ => encounter) }
        }
    }
}

let experiencePointForPeril = (peril : peril) => {
    switch(peril) {
        | SimpleDanger => 8
        | Creature     => 40
    }
}
let experiencePoints= (~encounter : encounter) => {
    map(encounter.perils, experiencePointForPeril) -> reduce(0, (a, b) => a + b)

}



