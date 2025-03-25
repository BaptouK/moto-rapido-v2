import {Form, FormControl, FormDescription, FormField, FormItem, FormLabel, FormMessage} from "@/components/ui/form";
import Image from "next/image";
import {Input} from "@/components/ui/input";
import {Button} from "@/components/ui/button";

import {cookies} from 'next/headers'

import {
    InputOTP,
    InputOTPGroup,
    InputOTPSeparator,
    InputOTPSlot,
} from "@/components/ui/input-otp";
import {Game, GamesTable} from "@/components/games-table";

const games :Game[] = [
    {id: "1", owner: "Alice", status: "waiting"},
    {id: "2", owner: "Bob", status: "playing"},
    {id: "3", owner: "Charlie", status: "ended"},
];


export default async function Games() {
    const cookieStore = await cookies()
    const username = cookieStore.get('username')?.value as string;

    return (
        <div className="flex flex-col items-center space-y-4 p-4">
            {/* Logo et connexion */}
            <Image src="/logo.png" alt="Logo" width={200} height={200} />
            <div className="text-center text-gray-500">Connecté en tant que {username}.</div>

            {/* Conteneur principal en flex */}
            <div className="flex w-full max-w-5xl border rounded-lg shadow-md p-4">
                {/* Partie gauche */}
                <div className="flex flex-col items-center flex-1 space-y-4">
                    {/* Rejoindre une partie*/}
                    <div className="text-lg">Rejoindre une partie</div>
                    <InputOTP maxLength={6}>
                        <InputOTPGroup>
                            <InputOTPSlot index={0} />
                            <InputOTPSlot index={1} />
                            <InputOTPSlot index={2} />
                        </InputOTPGroup>
                        <InputOTPSeparator />
                        <InputOTPGroup>
                            <InputOTPSlot index={3} />
                            <InputOTPSlot index={4} />
                            <InputOTPSlot index={5} />
                        </InputOTPGroup>
                    </InputOTP>
                    <div className="text-sm text-gray-500">Ou</div>
                    <Button className={"cursor-pointer"}>Créer une partie</Button>
                </div>

                {/* Séparateur vertical */}
                <div className="w-px bg-gray-300 mx-4" />

                {/* Partie droite */}
                <div className="flex-1 space-y-4">
                    {/* Liste des parties */}
                    <div className="text-center text-lg">Liste des parties</div>
                    <GamesTable games={games} />
                </div>
            </div>
        </div>
    )
}