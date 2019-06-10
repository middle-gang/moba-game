
#ifndef Moreau_LinkingContext_h
#define Moreau_LinkingContext_h

class ObjectBase;

class LinkingContext
{
public:
	
	LinkingContext() : 
	mNextNetworkId( 1 )
	{}

	uint32_t GetNetworkId( ObjectBase* inGameObject, bool inShouldCreateIfNotFound )
	{
		auto it = mGameObjectToNetworkIdMap.find( inGameObject );
		if( it != mGameObjectToNetworkIdMap.end() )
		{
			return it->second;
		}
		else if( inShouldCreateIfNotFound )
		{
			uint32_t newNetworkId = mNextNetworkId++;
			AddGameObject( inGameObject, newNetworkId );
			return newNetworkId;
		}
		else
		{
			return 0;
		}
	}
	
	ObjectBase* GetGameObject( uint32_t inNetworkId ) const
	{
		auto it = mNetworkIdToGameObjectMap.find( inNetworkId );
		if( it != mNetworkIdToGameObjectMap.end() )
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}

	void AddGameObject( ObjectBase* inGameObject, uint32_t inNetworkId )
	{
		mNetworkIdToGameObjectMap[ inNetworkId ] = inGameObject;
		mGameObjectToNetworkIdMap[ inGameObject ] = inNetworkId;
	}
	
	void RemoveGameObject( ObjectBase* inGameObject )
	{
		uint32_t networkId = mGameObjectToNetworkIdMap[ inGameObject ];
		mGameObjectToNetworkIdMap.erase( inGameObject );
		mNetworkIdToGameObjectMap.erase( networkId );
	}
	
private:
	std::unordered_map< uint32_t, GameObject* > mNetworkIdToGameObjectMap;
	std::unordered_map< const GameObject*, uint32_t > mGameObjectToNetworkIdMap;

	uint32_t mNextNetworkId;
};

#endif
