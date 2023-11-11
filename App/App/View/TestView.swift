import SwiftUI

struct ListView: View {
    @ObservedObject var model: ListModel // 使用 @ObservedObject 包装数据模型

    @State private var searchText = ""

    var body: some View {
        NavigationView {
            VStack {
                TextField("Search", text: $searchText)
                    .padding()
                    .textFieldStyle(RoundedBorderTextFieldStyle())

                List(filteredItems()) { item in
                    Text(item.name)
                }
            }
            .navigationBarTitle("Search Example")
        }
    }

    func filteredItems() -> [ListItem] {
        return model.items.filter {
            searchText.isEmpty ? true : $0.name.lowercased().contains(searchText.lowercased())
        }
    }
}
