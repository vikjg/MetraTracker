import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    property string hostingKey: "45d625993607419da245250ba70e8c35"

    Map {
        id: trainMap
        anchors.fill: parent
        plugin: Plugin {
            name: "osm"
            PluginParameter {
                name: "osm.mapping.providersrepository.disabled"
                value: true
            }
            PluginParameter {
                name: "osm.mapping.custom.host"
                value: "https://tile.thunderforest.com/pioneer/%z/%x/%y.png?apikey=" + hostingKey // use %z/%x/%y so new tilenumber.png is not appended
            }
        }
        activeMapType: trainMap.supportedMapTypes[trainMap.supportedMapTypes.length - 1]
        center: QtPositioning.coordinate(41.8781, -87.6298) // Chicago
        minimumZoomLevel: 6
        maximumZoomLevel: 15

        Slider {
            id: zoomSlider
            height: parent.height
            orientation: Qt.Vertical
            stepSize: 1
            snapMode: zoomSlider.SnapAlways
            from: trainMap.minimumZoomLevel
            to: trainMap.maximumZoomLevel
            value: trainMap.zoomLevel
            onValueChanged: {
                trainMap.zoomLevel = value
            }
        }

        MapItemView {
            id: mapItemView
            model: trainModel

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.latitude, model.longitude)
                anchorPoint: Qt.point(marker.width / 2, marker.height / 2)

                sourceItem: Rectangle {
                    id: marker
                    width: 12
                    height: 12
                    radius: 6
                    //color: "red"
                    border.color: "black"
                    Image{
                        source: "file:///home/viktor-giordano/Projects/Metra2/metra.png"
                        width: parent.width
                        height: parent.height
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
