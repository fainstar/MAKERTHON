import SwiftUI

struct MainControl: View {
    @StateObject var model = ListModel() // 创建 ListModel 并使用 @StateObject 包装

    var body: some View {
        TabView {
            FirstView()
                .tabItem {
                    Image(systemName:"square.and.pencil.circle.fill")
                        .font(.system(size: 30)) // 調整圖標的大小
                }
            ThirdView()
                .tabItem {
                    Image(systemName:"house.circle.fill")
                        .font(.system(size: 30)) // 調整圖標的大小
                }
            ListView(model: model) // 传递 ListModel 对象
                .tabItem {
                    Image(systemName:"square.and.pencil.circle.fill")
                        .font(.system(size: 30)) // 調整圖標的大小
                }
        }
    }
}

#Preview {
    MainControl()
}
