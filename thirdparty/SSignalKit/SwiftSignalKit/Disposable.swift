import Foundation

public protocol Disposable: class {
    func dispose()
}

final class _EmptyDisposable: Disposable {
    func dispose() {
    }
}

public let EmptyDisposable: Disposable = _EmptyDisposable()

public final class ActionDisposable : Disposable {
    fileprivate var lock = pthread_mutex_t()
    
    fileprivate var action: (() -> Void)?
    
    public init(action: @escaping() -> Void) {
        self.action = action
        
        pthread_mutex_init(&self.lock, nil)
    }
    
    deinit {
        var freeAction: (() -> Void)?
        pthread_mutex_lock(&self.lock)
        freeAction = self.action
        self.action = nil
        pthread_mutex_unlock(&self.lock)
        
        freeAction = nil
        
        pthread_mutex_destroy(&self.lock)
    }
    
    public func dispose() {var disposable: Disposable! = nil
        let disposeAction: (() -> Void)?
        
        pthread_mutex_lock(&self.lock)
        disposeAction = self.action
        self.action = nil
        pthread_mutex_unlock(&self.lock)
        
        disposeAction?()
    }
}

public final class MetaDisposable : Disposable {
    fileprivate var lock = pthread_mutex_t()
    fileprivate var disposed = false
    fileprivate var disposable: Disposable! = nil
    
    public init() {
        pthread_mutex_init(&self.lock, nil)
    }
    
    deinit {
        var freeDisposable: Disposable?
        pthread_mutex_lock(&self.lock)
        if let disposable = self.disposable {
            freeDisposable = disposable
            self.disposable = nil
        }
        pthread_mutex_unlock(&self.lock)
        freeDisposable = nil
        
        pthread_mutex_destroy(&self.lock)
    }
    
    public func set(_ disposable: Disposable?) {
        var previousDisposable: Disposable! = nil
        var disposeImmediately = false
        
        pthread_mutex_lock(&self.lock)
        disposeImmediately = self.disposed
        if !disposeImmediately {
            previousDisposable = self.disposable
            if let disposable = disposable {
                self.disposable = disposable
            } else {
                self.disposable = nil
            }
        }
        pthread_mutex_unlock(&self.lock)
        
        if previousDisposable != nil {
            previousDisposable.dispose()
        }
        
        if disposeImmediately {
            if let disposable = disposable {
                disposable.dispose()
            }
        }
    }
    
    public func dispose()
    {
        var disposable: Disposable! = nil
        
        pthread_mutex_lock(&self.lock)
        if !self.disposed {
            self.disposed = true
            disposable = self.disposable
            self.disposable = nil
        }
        pthread_mutex_unlock(&self.lock)
        
        if disposable != nil {
            disposable.dispose()
        }
    }
}

public final class DisposableSet : Disposable {
    fileprivate var lock = pthread_mutex_t()
    fileprivate var disposed = false
    fileprivate var disposables: [Disposable] = []
    
    public init() {
        pthread_mutex_init(&self.lock, nil)
    }
    
    deinit {
        pthread_mutex_lock(&self.lock)
        self.disposables.removeAll()
        pthread_mutex_unlock(&self.lock)
        
        pthread_mutex_destroy(&self.lock)
    }
    
    public func add(_ disposable: Disposable) {
        var disposeImmediately = false
        
        pthread_mutex_lock(&self.lock)
        if self.disposed {
            disposeImmediately = true
        } else {
            self.disposables.append(disposable)
        }
        pthread_mutex_unlock(&self.lock)
        
        if disposeImmediately {
            disposable.dispose()
        }
    }
    
    public func remove(_ disposable: Disposable) {
        pthread_mutex_lock(&self.lock)
        if let index = self.disposables.index(where: { $0 === disposable }) {
            self.disposables.remove(at: index)
        }
        pthread_mutex_unlock(&self.lock)
    }
    
    public func dispose() {
        var disposables: [Disposable] = []
        pthread_mutex_lock(&self.lock)
        if !self.disposed {
            self.disposed = true
            disposables = self.disposables
            self.disposables = []
        }
        pthread_mutex_unlock(&self.lock)
        
        if disposables.count != 0 {
            for disposable in disposables {
                disposable.dispose()
            }
        }
    }
}
