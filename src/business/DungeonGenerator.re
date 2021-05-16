open Belt.List;

type peril =
  | Creature
  | SimpleDanger;

type encounter = {perils: list(peril)};

type chooser = list(peril) => option(peril);

let pickRandom = (perils: list(peril)) => Belt.List.head(shuffle(perils));

let experiencePointForPeril = (peril: peril) => {
  switch (peril) {
  | SimpleDanger => 8
  | Creature => 40
  };
};
let experiencePoints = (~encounter: encounter) => {
  map(encounter.perils, experiencePointForPeril)->reduce(0, (a, b) => a + b);
};

let rec addPeril =
        (
          chooser: chooser,
          perils: list(peril),
          building: list(peril),
          goal: int,
        )
        : list(peril) =>
  if (0 == goal) {
    building;
  } else {
    let element =
      chooser(keep(perils, p => experiencePointForPeril(p) <= goal));
    switch (element) {
    | None => []
    | Some(peril) =>
      let newBuilding = building->add(peril);
      addPeril(
        chooser,
        perils,
        newBuilding,
        goal - experiencePointForPeril(peril),
      );
    };
  };

let generateEncounter =
    (~perils: array(peril), ~chooser: chooser=pickRandom, ()): encounter => {
  let perils = addPeril(chooser, fromArray(perils), [], 80);
  {perils: perils};
};
