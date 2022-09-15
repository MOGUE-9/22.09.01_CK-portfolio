#include "stdafx.h"

Scene01::Scene01()
{
    LIGHT->light.radius = 2000.0f;
    pl = new Player();
    mon = new Monster();
    boss = new Boss();

    weapon = new Weapon();
    
    pickAxe = new PickAxe();
    pickAxe->GearOff();

    sword = new Sword();
    sword->GearOff();
    
    torch = new Torch();


    mainBuild = new MainCore();


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


    map_RT = new ObTileMap();
    map_RT->file = "map1.txt";
    map_RT->Load();

    map_LT = new ObTileMap();
    map_LT->file = "map2.txt";
    map_LT->Load();


    ////map->CreateTileCost();
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
    SafeDelete(mon);
    SafeDelete(map_RT);
    SafeDelete(map_LT);

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

    //icons�� Type�� ���������� bag�� ������Ʈ ���ֱ�
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
   mon->SetTarget(pl->GetPos());
   boss->SetTarget(pl->GetPos());

    pl->Update();
    boss->Update();

    mon->Update();

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

    map_RT->Update();
    map_LT->Update();

    mainBuild->Update();

    CAM->position = pl->GetPos();
}

void Scene01::LateUpdate()
{
    //INPUT->GetMouseWorldPos()


    //if (torch->isInterSect(sword->ReturnHitBox()))
    //{
    //    cout << "�̰ŵ�?" << endl; //��!!!!
    //}

    if (sword->ReturnHitBox()->Intersect(torch->ReturnCol()))
    {
        //cout << "�̰ǵ�?" << endl;  //��!!!!
        sword->attackCoolTime();
        torch->GetPlayer(pl->GetPos());
        torch->GetHiBox(pl->ReturnColBox());

        torch->count--;                             
    }

    //���� ���� ������ ��!!
    if (sword->ReturnHitBox()->Intersect(mon->ReturnColBox()))
    {
        sword->attackCoolTime();
        mon->hp -= sword->att;

        //cout << "�� ü�� : " << mon->hp << endl;
    }
    //���Ͱ� �� ������ ��!!
    if (mon->ReturnColBox()->Intersect(pl->ReturnColBox()))
    {
        mon->fightMod = true;

        if (mon->getAttack)
        {
            pl->hp -= mon->att;
            mon->fightMod = false;
            mon->getAttack = false;
            //cout << "p : " << pl->hp << endl;
        }

    }
    else
    {
        mon->fightMod = false;
    }

    //���� ���� ������ ��!!
    if (sword->ReturnHitBox()->Intersect(boss->ReturnColBox()))
    {
        sword->attackCoolTime();
        boss->hp -= sword->att;

        cout << "�� ü�� : " << boss->hp << endl;
    }
    //������ �� ������ ��!!
    if (boss->ReturnColBox()->Intersect(pl->ReturnColBox()))
    {
        boss->fightMod = true;

        if (mon->getAttack)
        {
            pl->hp -= mon->att;
            boss->fightMod = false;
            boss->getAttack = false;
            //cout << "p : " << pl->hp << endl;
        }

    }
    else
    {
        boss->fightMod = false;
    }

    Int2 on;
    
    if (map_RT->WorldPosToTileIdx(pl->GetPos(), on))
    {
        ImGui::Text("TileState %d", map_RT->GetTileState(on));
        ImGui::Text("TileState %d", map_LT->GetTileState(on));

    }
    
    vector<Vector2>& Foot = pl->GetFoot();
    
    for (int i = 0; i < 4; i++)
    {
        Int2 on;
        if (map_RT->WorldPosToTileIdx(Foot[i], on))
        {
            if (map_RT->GetTileState(on) == TILE_WALL)
            {
                pl->StepBack();
            }
        }
        if (map_LT->WorldPosToTileIdx(Foot[i], on))
        {
            if (map_LT->GetTileState(on) == TILE_WALL)
            {
                pl->StepBack();
            }
        }
    }


}

void Scene01::Render()
{
    //                               L  T   R   B
    //DWRITE->RenderText(L"�ȳ�\n�ȳ�", RECT{ 300,100,(long)app.GetWidth(),(long)app.GetHalfHeight() },
    //    30.0f, L"�޸ո���ü", Color(1, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);


    map_RT->Render();
    map_LT->Render();
    mainBuild->Render();

    mon->Render();
    boss->Render();

    if (sword->GetWeaponDir() == 2)
    {
        pickAxe->Render();
        sword->Render();
        torch->Render();
        pl->Render();
    }
    else
    {
        pl->Render();
        pickAxe->Render();
        sword->Render();
        torch->Render();
    }




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
