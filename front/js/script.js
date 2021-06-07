// Kinepolis Location
// Variaves de Curuá
// var lat =-1.889366;
// var lng = -55.117389;
// Variaveis de Monte Alegre 
// var lat =-2.427046
// var lng = -54.713984
// Variaveis do Rio
var lat = -22.944993;
var lng = -43.181595;
// Variáveis do Amapá
var lat = -22.944993;
var lng = -43.181595;

//instância do mapa
var map = L.map('location-map').setView([lat, lng], 14);
//variável que armazena as lat/long de cada nó(é uma lista de listas: [[lat,long]])
var route = [];
//lista para armazenar os dois últimos cliques
var coord_list = [];
//marcadores de inicio e destino
var startMarker = L.marker(
    coord_list[0], {
        draggable:true,
        title: "Ponto de partida",})
    .bindPopup("<b>Marcador de</b><br />Início.")
    .openPopup();

var destinMarker = L.marker(
    coord_list[1],{
        draggable:true,
        title: "Ponto de destino",})
    .bindPopup("<b>Marcador de</b><br />Destino.")
    .openPopup();


var matchingGradient = [
    "#79BBD2",
    "#71A6CE",
    "#788FC2",
    "#8676AD",
    "#925C8E",
    "#944367",
]

function toMin(durationInSec) {
    return Math.round((durationInSec / 60)) + 'min.'
}

function legend() {
    var legend = L.control({position: 'bottomright'});
    legend.onAdd = function (map) {
        var div = L.DomUtil.create('div', 'info legend');
        div.innerHTML = '<h4>Travel time legend</h4>'
        isochrones.isochrones.forEach((iso, idx, allTab) => {
            var text = toMin(iso.min_duration) + ' &dash; ' + toMin(iso.max_duration)
            div.innerHTML +=
            '<i style="background:' + matchingGradient[idx] + '"></i> ' +
                text + (idx !== allTab.length - 1 ? '<br>' : '');
        })
        return div;
    };
    return legend;
}

//função que recebe o clique
function onMapClick(e) { 
    //add um marcador no local de clique
    L.marker(e.latlng,{clickable:true,draggable:true,title:"marca"}).bindPopup("<b>Marcadorzinho</b><br />Popup.").openPopup().addTo(map);
    //add a última coordenada na lista
    coord_list.push(e.latlng);
    //reseta a lista a cada dois cliques
    if (coord_list.length > 2) {
        coord_list = [];
        coord_list.push(e.latlng);
    };
    //add as coordendas na lista de nós
    route.push(e.latlng);
    //traça as linhas entre os nós
    var polyline = L.polyline(route,
        {
            opacity: 0.8,
            dashArray: "2 12",
            color: 'red',
            weight: 10,
            attribution: '&copy; Navitia'}).addTo(map);
    //zoom no trajeto
    //map.fitBounds(polyline.getBounds());
    //console.log(e.latlng);
}

// map.on('click', onMapClick).getBounds();

function init(){
    


    // Station Antwerpen Centraal
    //var stationLat = 51.217222;
    //var stationLng = 4.421111;

    var zoomLevel = 13;
    //const map = L.map('location-map').setView([lat, lng], zoomLevel);
    //var stationMarker = L.marker(
    //    [stationLat, stationLng],
    //    {
    //        title: "Antwerpen Centraal"
    //    }
    //).bindPopup('Hello station');
    //var circle = L.circle([stationLat, stationLng], 2000, {color: 'red'});

    //var journeyOverlay = journeyLine();

    //var stationJourneyLayer = L.layerGroup([journeyOverlay, circle, stationMarker])
    
    /*
    Tiles are numbered as {z}/{x}/{y} or {z}/{x}/{y}{r}, where
        - z is zoom,
        - x is the tile number from left to right,
        - y is the tile number from top to bottom.
        - r is for retina screen
    */
    
    var mapLink = '<a href="https://openstreetmap.org">OpenStreetMap</a>';
    // OpenStreetMap
    var mainLayer = L.tileLayer(
        'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
            attribution: 'Map data &copy; ' + mapLink,
            maxZoom: 20,
        });
    // Stamen Layer
    var stamenToner = L.tileLayer('http://stamen-tiles-{s}.a.ssl.fastly.net/toner/{z}/{x}/{y}.png', {
        attribution: 'Map tiles by Stamen Design, CC BY 3.0 — Map data © OpenStreetMap',
        subdomains: 'abcd',
        minZoom: 0,
        maxZoom: 20,
        ext: 'png'
    });
    var waterColor =  L.tileLayer('http://b.tile.stamen.com/watercolor/{z}/{x}/{y}.png', {
        attribution: 'Map tiles by Stamen Design, CC BY 3.0 — Map data © OpenStreetMap',
        subdomains: 'abcd',
        minZoom: 0,
        maxZoom: 20,
        ext: 'png'
    });
    
    // Public Transport
    var transportLayer = L.tileLayer('http://openptmap.org/tiles/{z}/{x}/{y}.png',{
        attribution: '&copy; <a href="http://openptmap.org/" target="_blank" rel="noopener noreferrer">OpenPTMap</a> / <a href="https://www.openstreetmap.org/copyright" target="_blank" rel="noopener noreferrer">OSM Contributors</a>',
        maxZoom: 22,
    })

    var ciclofaixas = L.geoJSON(ciclovias,
        {
            opacity: 0.8,
            dashArray: "2",
            color: 'brown',
            weight: 5,
            attribution: 'Ciclofaixas'
        });
    
    var metro = L.geoJSON(metroStations,
        {
            opacity: 0.8,
            dashArray: "2",
            color: 'brown',
            weight: 5,
            highway: 'bus_stop',
            attribution: 'Estações de metrô'
        });
    
    var biciclet = L.geoJSON(bicicletarios,
        {
            opacity: 0.8,
            dashArray: "2",
            color: 'brown',
            weight: 5,
            attribution: 'Bicicletários' 
        });


                  
    var legendControl = legend()

    

    var controlLayer = L.control.layers({
        'OpenStreetMap': mainLayer,
        'Stamen': stamenToner,
        'WaterColor': waterColor,
    }, {
        'Transport': transportLayer,
        'Ciclovias': ciclofaixas,
        'Metrô': metro,
        'Bicicletários': biciclet,
    })
    
    mainLayer.addTo(map);
    controlLayer.addTo(map);
    var customIcon = L.icon({
        iconUrl: 'assets/images/fgvbrasao.png',
        iconSize:     [70, 30], // tamanho do ícone
        iconAnchor:   [25, 25], // pino do ícone
    });
    var fgvMarker = L.marker(
        [lat, lng],
        {
            icon: customIcon,
            title: "FGV",
            riseOnHover: true,
        }
    );
    fgvMarker.bindPopup("<div class='fgv-popup'>FGV é aqui!<br><img src='assets/images/fgvLogo.png' width='200'></div>", {className: 'fgv-popup-container'})
    fgvMarker.bindTooltip("<span>Localização da FGV (Botafogo)</span>")
    fgvMarker.addTo(map);
}





function addNodes() {
    
}


//roda quando algo é escrito na entrada
function submitForm(event) {
    event.preventDefault();
    
    //atribuindo os dados de entrada e de saída
    begin = document.getElementById('start').value;
    end = document.getElementById('destination').value;
}

//retorna as coordenadas do endereço
function findAddress() {
    //instacia nominatin
    var geocoding_url = "https://nominatim.openstreetmap.org/search?format=json&limit=5&accept-language=pt-BR&countrycodes=br&q=";
    //variável para armazenar os resultados da busca
    var results = document.getElementById('results');

    if(start_input == document.activeElement) {
    //fetch para obter os resultados da busca
        var whichInput = 0;
        fetch(geocoding_url + start_input.value)
                .then(response => response.json())
                .then(data => fieldAddress = data)
                .then(show => showAddress(fieldAddress,whichInput))
                .catch(err => console.log(err));
        console.log("start ta em foco");
        
        
    }
    if(end_input == document.activeElement) {
        //fetch para obter os resultados da busca
            var whichInput = 1;
            fetch(geocoding_url + end_input.value)
                    .then(response => response.json())
                    .then(data => fieldAddress = data)
                    .then(show => showAddress(fieldAddress,whichInput))
                    .catch(err => console.log(err));
            console.log("end ta em foco");
        }
    return whichInput;
}

//exibe os resultados da busca
function showAddress(fieldAddress,whichInput) {
    results.innerHTML = ''
    //se a busca retorna resultados, eles são exibidos
    
    if(fieldAddress.length > 0) {
        fieldAddress.forEach(element => {
            var place_name = element.display_name.split(",", 3);
            results.innerHTML += 
            "<li onclick='select(["+element.lat+","+element.lon+"],"+whichInput+")'>" + 
            place_name + "</li>"
        });
        
    }
    if(fieldAddress.length == 0) {
        results.innerHTML += "<p style='color:[element.lat,element.lon] red> Nenhum resultado encontrado </p>"
        console.log(fieldAddress.length)
    }
};


function select(list,whichInput) {
    coord_list[whichInput]=list;
    console.log(coord_list[whichInput])

    startMarker.addTo(map);
    destinMarker.addTo(map);

    startMarker.setLatLng(coord_list[0]);
    destinMarker.setLatLng(coord_list[1]);

}


//////////////////////////////////
//variável para o form
const form = document.querySelector('form');
const all_input = document.querySelectorAll('input');
const start_input = form.querySelector('#start');
const end_input = form.querySelector('#destination');

//chama a função quando o form é enviado
form.addEventListener('submit', submitForm);
function select_input() {
    all_input.forEach(element => {
        element.addEventListener('focus', findAddress)
        console.log(element.id)
        element.onkeyup = (e)=>{
            
            console.log(e.target.value);
            findAddress(e.target.value);
        }
    })
}

select_input();



/////////////////////////////////////////////////////
