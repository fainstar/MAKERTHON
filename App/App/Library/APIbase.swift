import Foundation

class APIbase {
    // 定義 API 的基本 URL
    let baseURL: URL
    
    init(baseURL: URL) {
        self.baseURL = baseURL
    }
    
    // 執行 GET 請求的方法
    func get(path: String, completion: @escaping (Result<Data, Error>) -> Void) {
        // 建立完整的 URL
        let url = baseURL.appendingPathComponent(path)
        
        // 建立 GET 請求
        var request = URLRequest(url: url)
        request.httpMethod = "GET"
        
        // 使用 URLSession 進行請求
        let session = URLSession.shared
        let task = session.dataTask(with: request) { (data, response, error) in
            if let error = error {
                completion(.failure(error))
            } else if let data = data {
                completion(.success(data))
            }
        }
        task.resume()
    }
}
//
//// 使用示例
//if let baseURL = URL(string: "https://api.example.com") {
//    let apiClient = APIbase(baseURL: baseURL)
//    APIbase.get(path: "data") { result in
//        switch result {
//        case .success(let data):
//            // 在這裡處理數據
//            print("成功獲取數據")
//        case .failure(let error):
//            // 處理錯誤
//            print("請求錯誤：\(error)")
//        }
//    }
//}
