//
//  StatusLoader.swift
//  Pods
//
//  Created by Benjamin Baron on 2/12/16.
//
//

import Foundation
import Async

// TODO: Make sure that the status loader completes before making any other API calls, that way we have the correct redirect URL.
class StatusLoader: ApiLoader {
    
    fileprivate(set) var server: Server?
    
    fileprivate(set) var url: String
    fileprivate(set) var username: String
    fileprivate(set) var password: String

    fileprivate(set) var versionString: String?
    fileprivate(set) var majorVersion: Int?
    fileprivate(set) var minorVersion: Int?
    
    convenience init(server: Server) {
        let password = server.password ?? ""
        self.init(url: server.url, username: server.username, password: password)
        self.server = server
    }
    
    init(url: String, username: String, password: String) {
        self.url = url
        self.username = username
        self.password = password
        super.init()
    }
    
    override func createRequest() -> URLRequest {
        return URLRequest(subsonicAction: .ping, baseUrl: url, username: username, password: password)    
    }
    
    override func processResponse(root: RXMLElement) -> Bool {
        if root.tag == "subsonic-response" {
            self.versionString = root.attribute("version")
            if let versionString = self.versionString {
                let splitVersion = versionString.components(separatedBy: ".")
                let count = splitVersion.count
                if count > 0 {
                    self.majorVersion = Int(splitVersion[0])
                    if count > 1 {
                        self.minorVersion = Int(splitVersion[1])
                    }
                }
            }
            return true
        }
        else
        {
            // This is not a Subsonic server, so fail
            Async.main {
                self.failed(error: NSError(iSubCode: .notSubsonicServer))
            }
            return false
        }
    }
    
    override func failed(error: Error?) {
        if let error = error as? NSError {
            if error.code == 40 {
                // Incorrect credentials, so fail
                super.failed(error: NSError(iSubCode: .invalidCredentials))
                return
            } else if error.code == 60 {
                // Subsonic trial ended
                super.failed(error: NSError(iSubCode: .subsonicTrialExpired))
                return
            }
        }
        
        super.failed(error: error)
    }
}