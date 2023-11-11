import UIKit

class FirstViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "First"
    }
}

class SecondViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "Second"
    }
}

class ThirdViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "Third"
    }
}

class FourthViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        self.title = "Fourth"
    }
}

class TabBarController: UITabBarController {
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let firstVC = FirstViewController()
        let secondVC = SecondViewController()
        let thirdVC = ThirdViewController()
        let fourthVC = FourthViewController()
        
        firstVC.tabBarItem = UITabBarItem(title: "First", image: nil, tag: 0)
        secondVC.tabBarItem = UITabBarItem(title: "Second", image: nil, tag: 1)
        thirdVC.tabBarItem = UITabBarItem(title: "Third", image: nil, tag: 2)
        fourthVC.tabBarItem = UITabBarItem(title: "Fourth", image: nil, tag: 3)
        
        let viewControllers = [firstVC, secondVC, thirdVC, fourthVC]
        self.viewControllers = viewControllers
    }
}


