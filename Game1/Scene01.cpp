#include "stdafx.h"

Scene01::Scene01()
{
    LIGHT->light.radius = 2000.0f;
    pl = new Player();

    weapon = new Weapon();
    
    pickAxe = new PickAxe();
    pickAxe->GearOff();

    sword = new Sword();
    sword->GearOff();
    
    torch = new Torch();


    bags = new Bag();
    screenUI = new OnScreen();

    for (int y = 0; y < bagY; y++)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][y] = new Icon();
        }
    }
    icons[0][0]->AddItem(ItemType::WEAPON);


    //mon = new Monster();
    map = new ObTileMap();
    map->file = "map1.txt";
    map->Load();
    //map->CreateTileCost();
    //
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //

    /*m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();*/
}

Scene01::~Scene01()
{
    SafeDelete(pl);
    //SafeDelete(mon);
    //SafeDelete(map);
}

void Scene01::Init()
{
}

void Scene01::Release()
{
}

void Scene01::Update()
{
    //ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

    if (INPUT->KeyDown('Q'))
    {
        icons[0][0]->AddItem(ItemType::WEAPON);
    }



    if (INPUT->KeyDown(VK_TAB))
    {
        isOpenBag = !isOpenBag;
    }

    torch->GetPlayer(pl->GetPos());

    pickAxe->SetTarget(pl->GetPos());
    sword->SetTarget(pl->GetPos());

    //icons의 Type을 지속적으로 bag에 업데이트 해주기
    for (int y = 0; y < bagY; y++)
    {
        for (int x = 0; x < bagX; x++)
        {
            bags->SetBagitemType(x, y, icons[x][y]->GetItem());
        }
    }

    if (!isOpenBag)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][0]->SetIconPos(bags->GetHotbarPos(x));
        }
    }
    else
    {
        for (int y = 0; y < bagY; y++)
        {
            for (int x = 0; x < bagX; x++)
            {
                icons[x][y]->SetIconPos(bags->GetBagitemPos(x, y));
            }
        }
    }



   for (int x = 0; x < bagX; x++)
   {
       if (bags->ReturnCol()->Intersect(bags->ReturnHotbarCol(x)))
       {

           if (bags->GetBagitemType(x , 0) == ItemType::WEAPON)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               sword->GearOn();
               pickAxe->GearOff();
               torch->GearOff();
           }
           else if (bags->GetBagitemType(x, 0) == ItemType::TOOL)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               pickAxe->GearOn();
               sword->GearOff();
               torch->GearOff();
           }
           else if (bags->GetBagitemType(x, 0) == ItemType::TORCH)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               torch->GearOn();
               sword->GearOff();
               pickAxe->GearOff();
           }
           else if (bags->GetBagitemType(x, 0) == ItemType::NONE)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               sword->GearOff();
               pickAxe->GearOff();
               torch->GearOff();
           }
       }
   }

   screenUI->SetItemType(bags->GetItemType());


    //우클릭햇을때
    //if (INPUT->KeyDown(VK_RBUTTON))
    //{
    //    //   출발점, 도착점
    //    Int2 sour, dest;
    //    //찾았는가?
    //    bool isFind;
    //
    //    isFind = map->WorldPosToTileIdx(pl->GetPos(), sour);
    //    isFind &= map->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), dest);
    //
    //    //둘다 타일맵 위에있을때
    //    if (isFind)
    //    {
    //        //길이 존재한다면
    //        if (map->PathFinding(sour, dest, PlWay))
    //        {
    //            //길 사이즈만큼 반복
    //            for (int i = 0; i < PlWay.size(); i++)
    //            {
    //                cout << "Way" << i << ":" << PlWay[i]->idx.x <<
    //                    "," << PlWay[i]->idx.y << endl;
    //            }
    //            g = 0.0f;
    //            PlSour = pl->GetPos();
    //            PlWay.pop_back(); //출발지 빼기
    //            PlDest = PlWay.back()->Pos;
    //        }
    //
    //    }
    //
    //}
    //
    //가야될 길이 존재할 때
    //if (!PlWay.empty())
    //{
    //    //PlSour = pl->GetPos();
    //    pl->SetPos(Utility::Lerp(PlSour, PlDest, g));
    //    g += DELTA * 3.0f;
    //
    //    //도착지를 지났을때
    //    if (g > 1.0f)
    //    {
    //        g = 0.0f;
    //        PlSour = PlDest;
    //        PlWay.pop_back(); //맨뒷길 빼기
    //        if (!PlWay.empty())
    //            PlDest = PlWay.back()->Pos;
    //    }
    //}

    pl->Update();

    pickAxe->Update();
    sword->Update();
    torch->Update();

    bags->Update();
    screenUI->Update();

    for (int y = 0; y < bagY; y++)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][y]->Update();
        }
    }

    //mon->SetTarget(pl->GetPos());
    //mon->Update();
    map->Update();

    CAM->position = pl->GetPos();
}

void Scene01::LateUpdate()
{
    //INPUT->GetMouseWorldPos()








    //if (torch->isInterSect(sword->ReturnHitBox()))
    //{
    //    cout << "이거됨?" << endl; //됨!!!!
    //}

    if (sword->ReturnHitBox()->Intersect(torch->ReturnCol()))
    {
        //cout << "이건돼?" << endl;  //됨!!!!
        sword->attackCoolTime();
        torch->GetPlayer(pl->GetPos());
        torch->GetHiBox(pl->ReturnColBox());

        torch->count--;
    }


    //Int2 on;
    //
    //if (map->WorldPosToTileIdx(pl->GetPos(), on))
    //{
    //    ImGui::Text("TileState %d", map->GetTileState(on));
    //}
    //
    //vector<Vector2>& Foot = pl->GetFoot();
    //
    //for (int i = 0; i < 4; i++)
    //{
    //    Int2 on;
    //    if (map->WorldPosToTileIdx(Foot[i], on))
    //    {
    //        if (map->GetTileState(on) == TILE_WALL)
    //        {
    //            pl->StepBack();
    //        }
    //    }
    //}


}

void Scene01::Render()
{
    //                               L  T   R   B
    //DWRITE->RenderText(L"안녕\n안녕", RECT{ 300,100,(long)app.GetWidth(),(long)app.GetHalfHeight() },
    //    30.0f, L"휴먼매직체", Color(1, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);


    //map->Render();

    
    if (sword->GetWeaponDir() == 2)
    {
        //pickAxe->Render();
        sword->Render();
        torch->Render();
        pl->Render();
    }
    else
    {
        pl->Render();
        //pickAxe->Render();
        sword->Render();
        torch->Render();
    }

    //mon->Render();



    bags->Render();
    screenUI->Render();


    if (!isOpenBag)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][0]->Render();
        }
    }
    else
    {
        for (int y = 0; y < bagY; y++)
        {
            for (int x = 0; x < bagX; x++)
            {
                icons[x][y]->Render();
            }
        }
    }

    //for (int y = 0; y < bagY; y++)
    //{
    //    for (int x = 0; x < bagX; x++)
    //    {
    //        icons[x][y]->Render();
    //    }
    //}
}

void Scene01::ResizeScreen()
{
}
