import Foundation

class ListModel: ObservableObject {
    @Published var items: [ListItem] = []

    init() {
        // 在这里初始化数据，这只是一个示例
        items = [
            ListItem(name: "Item 1"),
            ListItem(name: "Item 2"),
            ListItem(name: "Item 3"),
            ListItem(name: "Item 4"),
            ListItem(name: "Item 5"),
        ]
    }
}

struct ListItem: Identifiable {
    var id = UUID()
    var name: String
}
