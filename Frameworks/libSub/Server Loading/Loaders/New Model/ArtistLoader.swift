//
//  ArtistLoader.swift
//  iSub
//
//  Created by Benjamin Baron on 1/4/17.
//  Copyright © 2017 Ben Baron. All rights reserved.
//

import Foundation

class ArtistLoader: ISMSLoader, ItemLoader {
    let artistId: Int
    
    var albums = [ISMSAlbum]()
    
    var items: [ISMSItem] {
        return albums
    }
    
    init(artistId: Int) {
        self.artistId = artistId
        super.init()
    }
    
    override func createRequest() -> URLRequest? {
        let parameters = ["id": "\(artistId)"]
        return NSMutableURLRequest(susAction: "getArtist", parameters: parameters) as URLRequest
    }
    
    override func processResponse() {
        guard let root = RXMLElement(fromXMLData: self.receivedData), root.isValid else {
            let error = NSError(ismsCode: ISMSErrorCode_NotXML)
            self.informDelegateLoadingFailed(error)
            return
        }
        
        if let error = root.child("error"), error.isValid {
            let code = error.attribute("code") ?? "-1"
            let message = error.attribute("message")
            self.subsonicErrorCode(Int(code) ?? -1, message: message)
        } else {
            var albumsTemp = [ISMSAlbum]()
            
            let serverId = SavedSettings.sharedInstance().currentServerId
            root.iterate("artist.album") { album in
                let anAlbum = ISMSAlbum(rxmlElement: album, serverId: serverId)
                albumsTemp.append(anAlbum)
            }
            albums = albumsTemp
            
            self.persistModels()
            
            self.informDelegateLoadingFinished()
        }
    }
    
    func persistModels() {
        // Save the new albums
        albums.forEach({$0.replace()})
    }
    
    func loadModelsFromCache() -> Bool {
        let serverId = SavedSettings.sharedInstance().currentServerId
        albums = ISMSAlbum.albums(inArtist: self.artistId, serverId: serverId)
        return albums.count > 0
    }
    
    var associatedObject: Any? {
        return ISMSArtist(artistId: artistId, serverId: SavedSettings.sharedInstance().currentServerId, loadSubmodels: false)
    }
}
