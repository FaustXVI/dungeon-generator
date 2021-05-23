open Belt.List;

type peril =
  | Creature
  | SimpleDanger
  | ComplexDanger;

type encounter = {perils: list((peril, int))};

type chooser = list(peril) => option(peril);

let pickRandom = (perils: list(peril)) => head(shuffle(perils));

let experiencePointForPeril = (peril: peril) => {
  switch (peril) {
  | SimpleDanger => 8
  | Creature
  | ComplexDanger => 40
  };
};
let experiencePoints = (~encounter: encounter) => {
  map(encounter.perils, ((p, n)) => n * experiencePointForPeril(p))
  ->reduce(0, (a, b) => a + b);
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

module PerilComparator =
  Belt.Id.MakeComparable({
    type t = peril;
    let cmp = (a: peril, b: peril) => compare(a, b);
  });

let generateEncounter =
    (~perils: array(peril), ~chooser: chooser=pickRandom, ()): encounter => {
  let m: Belt.Map.t(peril, int, PerilComparator.identity) =
    Belt.Map.make(~id=(module PerilComparator));
  let perils =
    addPeril(chooser, fromArray(perils), [], 80)
    ->map(p => (p, 1))
    ->reduce(m, (acc, (p, n)) =>
        acc->Belt.Map.update(p, v => {
          switch (v) {
          | None => Some(1)
          | Some(x) => Some(x + n)
          }
        })
      );
  {perils: Belt.Map.toList(perils)};
};
