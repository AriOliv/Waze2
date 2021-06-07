// // Cleaning the data
// var streets2 = {}
// let key;
// for (let index = 0; index < streets1["features"].length; index++) {
//     // dict_temp = {};
//     // dict_temp["type"] = "FeatureCollection";
//     // dict_temp["features"]=[];
//     const element = streets1["features"][index];
//     key = element["properties"]["u"];
//     streets2[key] = [];
// }

// for (let index = 0; index < streets1["features"].length; index++) {
//     const element = streets1["features"][index];
//     key = element["properties"]["u"];

//     dict_temp = {};
//     dict_temp["type"] = "FeatureCollection";
//     dict_temp["features"] = [element];

//     streets2[key].push(dict_temp);
// }
// let jsoff = document.createElement("p")


class A_Path {
    constructor(y1, x1, y2, x2) {
        fetch(`../../back/graph_class.cgi?${y1};${x1};${y2};${x2}`).then(this.onSucess.bind(this))
    }
    onSucess(response) {
        response.text().then(this.onProcessed.bind(this));
    }

    onProcessed(text) {
        this.node_path = eval(text);
        console.log(this.node_path);
        this.draw_path_by_id();
    }
    draw_path_by_coordinate() {
        let rota = [];
        for (let index = 0; index < this.node_path.length; index++) {
            const element = this.node_path[index];
            rota.push(new L.LatLng(element["y"], element["x"]))
        }
        L.polyline(rota,
            {
                opacity: 0.8,
                dashArray: "2 12",
                color: 'blue',
                weight: 7,
                attribution: '&copy; Navitia'
            }).addTo(map)
    }
    draw_path_by_id() {
        console.log("Desenhando....");
        for (let index = 1; index < this.node_path.length; index++) {
            const id_from = this.node_path[index - 1];
            const id_to = this.node_path[index];
            write_path_by_id(id_from, id_to)
        }
    }
}

class Dijkstra_Path {
    constructor(y1, x1, y2, x2) {
        fetch(`../../back/dijkstra.cgi?${y1};${x1};${y2};${x2}`).then(this.onSucess.bind(this))
    }
    onSucess(response) {
        response.text().then(this.onProcessed.bind(this));
    }
    onProcessed(text) {
        console.log(text)
        this.node_path = eval(text);
        console.log(this.node_path);
        this.draw_path_by_id();
    }
    draw_path() {
        let rota = [];
        for (let index = 0; index < this.node_path.length; index++) {
            const element = this.node_path[index];
            rota.push(new L.LatLng(element["y"], element["x"]))
        }
        L.polyline(rota,
            {
                opacity: 0.8,
                dashArray: "2 12",
                color: 'blue',
                weight: 7,
                attribution: '&copy; Navitia'
            }).addTo(map)
    }
    draw_path_by_id() {
        for (let index = 1; index < this.node_path.length; index++) {
            const id_from = this.node_path[index - 1];
            const id_to = this.node_path[index];
            write_path_by_id(id_from, id_to);
        }
    }
}

function write_path_by_id(id_to, id_from) {
    let id_from_neighbors = streets2[id_from]
    let element;
    let edge;
    console.log(id_from_neighbors)
    console.log(id_from_neighbors)
    for (let index = 0; index < id_from_neighbors.length; index++) {
        element = id_from_neighbors[index];
        if (element["features"][0]["properties"]["v"] == id_to) {
            edge = element;
            console.log(element)
        }
    }
    
    L.geoJSON(edge,
        {
            style: function (feature) {
                console.log("Adicionando path")
                return {
                    stroke: true,
                    color: "red",
                    weight: 5
                }
            }
        }).addTo(map);
    // streets_temp = {}
    // streets_temp["type"] = "FeatureCollection";
    // streets_temp["features"] = []
    // for (let index = 0; index < streets1["features"].length; index++) {
    //     const element = streets1["features"][index]
    //     if (element["properties"]["u"] == id_from & element["properties"]["v"] == id_to) {
    //         streets_temp["features"].push(element)
    //     }
    // }
    // console.log(streets_temp);
    // console.log(element);
    // L.geoJSON(streets_temp,
    //     {
    //         style: function (feature) {
    //             if (feature["properties"]["u"] == id_from & feature["properties"]["v"] == id_to) {
    //                 return {
    //                     stroke: true,
    //                     color: "red",
    //                     weight: 5
    //                 }
    //             } else {
    //                 return { stroke: false }
    //             }

    //         }
    //     }).addTo(map);
}


map.on('click', add_path);
var coordenadas = []
let x1; let y1; let x2; let y2;
function add_path(e) {
    coordenadas.push(e.latlng);
    // console.log(e.latlng);
    L.marker(e.latlng, { draggable: true }).addTo(map);
    if (coordenadas.length == 2) {
        // console.log(coordenadas);
        x1 = coordenadas[0]['lng']
        y1 = coordenadas[0]['lat']
        x2 = coordenadas[1]['lng']
        y2 = coordenadas[1]['lat']
        const caminho = new A_Path(y1, x1, y2, x2);
        coordenadas = []
    }
}



// console.log(streets1["features"]);

